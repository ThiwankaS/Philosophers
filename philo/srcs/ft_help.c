/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:24 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/10 00:23:22 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	life(t_philo *philo)
{
	printf("{%d} is thinking\n", philo->id);
	sem_wait(&philo->rules->cycle_fork);
	pthread_mutex_lock(&philo->fork_l->fork);
	printf("{%d} has taken fork {%d}\n", philo->id, philo->fork_l->id);
	pthread_mutex_lock(&philo->fork_r->fork);
	printf("{%d} has taken fork {%d}\n", philo->id, philo->fork_r->id);
	printf("{%d} is eating\n", philo->id);
	sleep(philo->time_eat);
	pthread_mutex_unlock(&philo->fork_l->fork);
	pthread_mutex_unlock(&philo->fork_r->fork);
	sem_post(&philo->rules->cycle_fork);
	return (1);
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
		life(philo);
	return (NULL);
}

int	ft_set_table(t_table *table, int size)
{
	int		count;
	t_philo	*philo;
	t_mutex	*mutex;

	count = 0;
	while (count < size)
	{
		mutex = &table->froks[count].fork;
		philo = &table->philos[count];
		if ((pthread_mutex_init(mutex, NULL)) != 0
			|| (pthread_create(&philo->thread, NULL, simulation, philo)) != 0)
			return (0);
		count++;
	}
	count = 0;
	while (count < size)
	{
		mutex = &table->froks[count].fork;
		philo = &table->philos[count];
		if ((pthread_join(philo->thread, NULL)) != 0
			|| (pthread_mutex_destroy(mutex)) != 0)
			return (0);
		count++;
	}
	return (1);
}
