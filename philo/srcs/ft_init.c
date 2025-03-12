/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 06:30:11 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/12 07:50:11 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*ft_init_forks(int size)
{
	t_fork	*forks;
	int		count;

	count = 0;
	forks = malloc(sizeof(t_fork) * size);
	if (!forks)
		return (NULL);
	while (count < size)
	{
		forks[count].id = count + 1;
		count++;
	}
	return (forks);
}

int	ft_init_table(	t_table	*table)
{
	table->is_alive = 1;
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
	return (1);
}

static int	ft_set_param(t_philo *philo, char *argv[])
{
	size_t	current_time;

	current_time = get_current_time();
	philo->time_die = ft_atol(argv[2]);
	philo->time_eat = ft_atol(argv[3]);
	philo->time_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->meal_to_eat = ft_atol(argv[5]);
	else
		philo->meal_to_eat = -1;
	philo->meal_eaten = 0;
	philo->time_last_meal = current_time;
	philo->time_born = current_time;
	return (1);
}

t_philo	*ft_init_philos(t_fork *forks, t_table *table, char *argv[], int size)
{
	t_philo	*philos;
	int		count;

	count = 0;
	philos = malloc(sizeof(t_philo) * size);
	if (!philos || !forks || !table)
		return (NULL);
	while (count < size)
	{
		philos[count].id = count + 1;
		philos[count].size = size;
		philos[count].fork_l = &forks[count];
		if (count == (size -1))
			philos[count].fork_r = &forks[0];
		else
			philos[count].fork_r = &forks[count + 1];
		philos[count].is_alive = &table->is_alive;
		philos[count].dead_lock = &table->dead_lock;
		philos[count].meal_lock = &table->meal_lock;
		philos[count].write_lock = &table->write_lock;
		ft_set_param(&philos[count], argv);
		count++;
	}
	return (philos);
}

