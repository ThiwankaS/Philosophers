/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:24 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/08 06:08:58 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool ft_validate_args(int argc, char *argv[])
{
	int		count;
	long	num;

	count = 1;
	if (argc < 5 || argc > 6)
		ft_error("[ INCORRECT NO OF ARGUMENTS! ]\n");
	while (count < argc)
	{
		num = ft_atoi(argv[count]);
		if (count == 1 && (num < 1 || num > MAX_PHILO))
			ft_error("[ INCORRECT NO OF PHILOSOPHERS! ]\n");
		else if (count == 5 && (num < 0 || num > INT_MAX))
			ft_error("[ INVALID ARGUMENTS FOR NO OF MEALS! ]\n");
		else if (count != 1 && count != 5 && (num < 1 || num > INT_MAX))
			ft_error("[ INVALID ARGUMENTS! ]\n");
		count++;
	}
	return (true);
}

void	*obsorver(void *ptr)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)ptr;
	while (true)
	{
		i = -1;
		while (++i < philos[0].philo_count)
		{
			pthread_mutex_lock(philos->mutexes.meal_lock);
			if (get_current_time() - philos[i].times.last_meal
				> philos[i].times.die)
			{
				pthread_mutex_unlock(philos->mutexes.meal_lock);
				print_action(&philos[i]," died ");
				pthread_mutex_lock(philos->mutexes.write_lock);
				return (NULL);
			}
			pthread_mutex_unlock(philos->mutexes.meal_lock);
		}
		if (is_all_eat(philos))
			return (NULL);
	}
	return (NULL);
}

int ft_launcher(t_table *table, int size)
{
	t_id	obsorver_id;
	int		count;

	count = 0;
	if (pthread_create(&obsorver_id, NULL, &obsorver, table->philos) != 0)
		destroy_all(table, "[ THREAD CREATION FAILED! ]\n", size, 1);
	while (count < size)
	{
		if (pthread_create(&table->philos[count].thread_id, NULL,
				start_simulation, &table->philos[count]) != 0)
			destroy_all(table, "[ THREAD CREATION FAILED! ]\n", size, 1);
		count++;
	}
	count = 0;
	if (pthread_join(obsorver_id, NULL) != 0)
		destroy_all(table, "[ THREAD JOIN FAILED! ]\n", size, 1);
	while (count < size)
	{
		if (pthread_detach(table->philos[count].thread_id) != 0)
			destroy_all(table, "[ THREAD DETACH FAILED! ]\n", size, 1);
		count++;
	}
	return (1);
}

void	*start_simulation(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->mutexes.meal_lock);
	philo->times.born_time = get_current_time();
	philo->times.last_meal = get_current_time();
	pthread_mutex_unlock(philo->mutexes.meal_lock);
	think(philo);
	while (true)
		philo_routine(philo);
	return (NULL);
}

void	destroy_all(t_table *engine, char *str, int count, int signal)
{
	while (--count >= 0)
		pthread_mutex_destroy(&engine->forks[count]);
	pthread_mutex_destroy(&engine->write_lock);
	pthread_mutex_destroy(&engine->meal_lock);
	if(engine->forks)
		free(engine->forks);
	if(engine->philos)
		free(engine->philos);
	if(engine)
		free(engine);
	error_message(str, signal);
}
