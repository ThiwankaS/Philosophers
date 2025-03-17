/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:24 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/16 23:31:09 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->is_alive) == 0)
		return (pthread_mutex_unlock(philo->dead_lock), 0);
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

int	has_all_eaten(t_philo *philos, int meals, int size)
{
	int	count;
	int	finished_eating;

	count = 0;
	finished_eating = 0;
	if (meals == -1)
		return (0);
	pthread_mutex_lock(philos[0].meal_lock);
	while (count < size)
	{
		if (philos[count].meal_eaten >= meals)
			finished_eating++;
		count++;
	}
	pthread_mutex_unlock(philos[0].meal_lock);
	pthread_mutex_lock(philos[0].write_lock);
	if (finished_eating == size)
	{
		*(philos[0].is_alive) = 0;
		return (pthread_mutex_unlock(philos[0].write_lock), 0);
	}
	return (pthread_mutex_unlock(philos[0].write_lock), 1);
}

int	has_died(t_philo *philos, int size)
{
	int		count;
	t_philo	p;

	count = 0;
	while (count < size)
	{
		p = philos[count];
		pthread_mutex_lock(philos[0].write_lock);
		if ((p.is_eating == 0)
			&& get_current_time() - p.time_last_meal > p.time_die)
		{
			*(philos[0].is_alive) = 0;
			return (pthread_mutex_unlock(philos[0].write_lock), 0);
		}
		pthread_mutex_unlock(philos[0].write_lock);
		count++;
	}
	return (1);
}

void	*obsrev(void *arg)
{
	int		size;
	int		meals;
	t_philo	*philos;

	philos = (t_philo *)arg;
	size = philos[0].size;
	meals = philos[0].meal_to_eat;
	ft_usleep(5);
	while (1)
	{
		if (!has_all_eaten(philos, meals, size) || !has_died(philos, size))
			break ;
	}
	return (NULL);
}

int	ft_set_table(t_table *table, int size)
{
	int			count;
	t_philo		*philos;
	t_fork		*forks;
	pthread_t	observe_therad;

	philos = table->philos;
	forks = table->froks;
	pthread_create(&observe_therad, NULL, &obsrev, table->philos);
	count = -1;
	while (++count < size)
		pthread_mutex_init(&forks[count].fork, NULL);
	count = -1;
	while (++count < size)
		pthread_create(&philos[count].thread, NULL, ft_sml, &philos[count]);
	count = -1;
	while (++count < size)
		pthread_join(philos[count].thread, NULL);
	pthread_join(observe_therad, NULL);
	return (1);
}
