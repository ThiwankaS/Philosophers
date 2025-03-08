/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 06:30:11 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/08 06:28:08 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_philos(t_table *tb, t_philo *ph, t_mutex *fk, char **argv)
{
	int	count;

	count = 0;
	while (count < ft_atoi(argv[1]))
	{
		ph[count].id = count + 1;
		ph[count].times.die = ft_atoi(argv[2]);
		ph[count].times.eat = ft_atoi(argv[3]);
		ph[count].times.sleep = ft_atoi(argv[4]);
		ph[count].times.last_meal = get_current_time();
		ph[count].times.born_time = get_current_time();
		ph[count].must_eat = -1;
		if (argv[5])
			ph[count].must_eat = ft_atoi(argv[5]);
		ph[count].meals_eaten = 0;
		ph[count].philo_count = ft_atoi(argv[1]);
		ph[count].mutexes.left_fork = &fk[count];
		if (count == 0)
			ph[count].mutexes.right_fork = &fk[ph[count].philo_count - 1];
		else
			ph[count].mutexes.right_fork = &fk[count - 1];
		ph[count].mutexes.write_lock = &tb->write_lock;
		ph[count].mutexes.meal_lock = &tb->meal_lock;
		count++;
	}
	return (1);
}

int	ft_init_forks(t_table *table, t_mutex *forks, int size)
{
	int	count;

	count = 0;
	while (count < size)
	{
		if (pthread_mutex_init(&forks[count], NULL) != 0)
			destroy_all(table, "[ FAILED TO INITIALIZED FORKS! ]\n", count, 1);
		count++;
	}
	return (1);
}

int	ft_set_table(t_table *table, t_philo *philos, t_mutex *forks)
{
	table->forks = forks;
	table->philos = philos;
	if (pthread_mutex_init(&table->write_lock, NULL) != 0
		|| pthread_mutex_init(&table->meal_lock, NULL) != 0)
		destroy_all(table, "[ FAILED TO INITIALIZED THE TABLE! ]\n", -1, 1);
	return (1);
}

bool	is_all_eat(t_philo *philos)
{
	int		finished;
	int		i;

	i = -1;
	finished = 0;
	if (philos[0].must_eat == -1)
		return (false);
	while (++i < philos[0].philo_count)
	{
		pthread_mutex_lock(philos->mutexes.meal_lock);
		if (philos[i].meals_eaten >= philos[i].must_eat)
			++finished;
		pthread_mutex_unlock(philos->mutexes.meal_lock);
	}
	if (finished == philos[0].philo_count)
	{
		pthread_mutex_lock(philos->mutexes.write_lock);
		return (true);
	}
	return (false);
}

void	think(t_philo *philo)
{
	size_t think;
	pthread_mutex_lock(philo->mutexes.meal_lock);
	think = (philo->times.die - (get_current_time() - philo->times.last_meal) - philo->times.eat - philo->times.sleep);
	pthread_mutex_unlock(philo->mutexes.meal_lock);
	print_action(philo, " is thinking");
	ft_usleep(think/2);
}

void	philo_routine(t_philo *philo)
{
	if(philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->mutexes.right_fork);
		print_action(philo, " has taken a fork");
		pthread_mutex_lock(philo->mutexes.left_fork);
		print_action(philo, " has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->mutexes.left_fork);
		print_action(philo, " has taken a fork");
		pthread_mutex_lock(philo->mutexes.right_fork);
		print_action(philo, " has taken a fork");
	}
	pthread_mutex_lock(philo->mutexes.meal_lock);
	philo->times.last_meal = get_current_time();
	print_action(philo, " is eating");
	philo->meals_eaten += 1;
	pthread_mutex_unlock(philo->mutexes.meal_lock);
	ft_usleep(philo->times.eat);
	pthread_mutex_unlock(philo->mutexes.left_fork);
	pthread_mutex_unlock(philo->mutexes.right_fork);
	print_action(philo, " is sleeping");
	ft_usleep(philo->times.sleep);
	think(philo);
}
