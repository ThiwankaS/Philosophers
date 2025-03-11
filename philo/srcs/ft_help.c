/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:24 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/11 05:57:41 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_sleep(t_philo *philo)
{
	ft_print_action(philo, "is sleeping");
	ft_usleep(philo->time_sleep);
	return (1);
}

int ft_think(t_philo *philo)
{
	ft_print_action(philo, "is thinking");
	return (1);
}

int ft_eat(t_philo *philo)
{
	sem_wait(&philo->rules->cycle_fork);

	pthread_mutex_lock(&philo->fork_l->fork);
	ft_print_action(philo, "has taken a fork");

	pthread_mutex_lock(&philo->fork_r->fork);
	ft_print_action(philo, "has taken a fork");

	pthread_mutex_lock(&philo->rules->meal_lock);
	philo->time_last_meal = get_current_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->rules->meal_lock);

	ft_print_action(philo, "is eating");
	ft_usleep(philo->time_eat);

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
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
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
