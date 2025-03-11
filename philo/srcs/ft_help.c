/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:24 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/11 12:12:51 by tsomacha         ###   ########.fr       */
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

int has_all_eaten(t_philo *philos, int meals, int size)
{
	int count = 0;
	t_mutex *lock = &philos[0].rules->meal_lock;
	if(meals == -1)
		return (0);
	else
	{
		while(count < size)
		{
			pthread_mutex_lock(lock);
			if(philos[count].meal_eaten > meals)
				return (1);
			pthread_mutex_unlock(lock);
			count++;
		}
		return (0);
	}
}

int ft_drama(t_table *table, int size)
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

void *obsrev(void *arg)
{
	int size;
	int meals;
	t_table *table;

	table = (t_table *)arg;
	size = table->philos[0].size;
	meals = table->philos[0].meal_to_eat;
	while(!has_all_eaten(table->philos, meals, size))
	{
		ft_drama(table, size);
	}
	return (NULL);
}

int	ft_set_table(t_table *table)
{
	pthread_t observe_therad;

	pthread_create(&observe_therad, NULL, &obsrev, table);
	pthread_join(observe_therad, NULL);
	return (1);
}
