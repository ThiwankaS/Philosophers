/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:24 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/13 14:44:21 by tsomacha         ###   ########.fr       */
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
	sem_wait(philo->cycle);
	if(philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_l->fork);
		ft_print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork_r->fork);
		ft_print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->fork_r->fork);
		ft_print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork_l->fork);
		ft_print_action(philo, "has taken a fork");
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->is_eating = 1;
	philo->time_last_meal = get_current_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_print_action(philo, "is eating");
	ft_usleep(philo->time_eat);
	pthread_mutex_lock(philo->write_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_unlock(&philo->fork_l->fork);
	pthread_mutex_unlock(&philo->fork_r->fork);
	sem_post(philo->cycle);
	return (1);
}

int is_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->is_alive) == 0)
		return (pthread_mutex_unlock(philo->dead_lock), 0);
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

void	*simulation(void *arg)
{
	t_philo	*philo;
	int flag = 1;

	philo = (t_philo *)arg;
	while (flag)
	{
		pthread_mutex_lock(philo->write_lock);
		if (*philo->is_alive == 0)
			flag = 0;
		pthread_mutex_unlock(philo->write_lock);
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	ft_print_action(philo,"died");
	return (NULL);
}

int has_all_eaten(t_philo *philos, int meals, int size)
{
	int	count;
	int	finished_eating;

	count = 0;
	finished_eating = 0;
	if (meals == -1)
		return (0);
	pthread_mutex_lock(philos[0].meal_lock);
	while (count < size)
	{		if (philos[count].meal_eaten >= meals)
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

void *obsrev(void *arg)
{
	int size;
	int meals;
	t_philo *philos;

	philos = (t_philo *)arg;
	size = philos[0].size;
	meals = philos[0].meal_to_eat;
	ft_usleep(5);
	while(1)
	{
		if(!has_all_eaten(philos, meals, size))
			break;
	}
	return (arg);
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
	count = 0;
	while (count < size)
	{
		pthread_mutex_init(&forks[count].fork, NULL);
		count++;
	}
	count = 0;
	while (count < size)
	{
		pthread_create(&philos[count].thread, NULL, simulation, &philos[count]);
		count++;
	}
	count = 0;
	while(count < size)
	{
		pthread_join(philos[count].thread, NULL);
		count++;
	}
	pthread_join(observe_therad, NULL);
	return (1);
}
