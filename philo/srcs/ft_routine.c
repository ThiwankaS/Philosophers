/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:02:01 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/16 23:46:32 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sleep(t_philo *philo)
{
	ft_print_action(philo, "is sleeping");
	ft_usleep(philo->time_sleep);
	return (1);
}

int	ft_think(t_philo *philo)
{
	ft_print_action(philo, "is thinking");
	return (1);
}

static int	ft_pick_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
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
	return (1);
}

int	ft_eat(t_philo *philo)
{
	ft_pick_fork(philo);
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
	return (1);
}

void	*ft_sml(void *arg)
{
	t_philo	*philo;
	int		flag;

	flag = 1;
	philo = (t_philo *)arg;
	if (philo->size == 1)
	{
		ft_usleep(philo->time_die);
		ft_print_action(philo, "died");
		return (NULL);
	}
	while (flag)
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
		pthread_mutex_lock(philo->write_lock);
		if (*philo->is_alive == 0)
			flag = 0;
		pthread_mutex_unlock(philo->write_lock);
	}
	return (NULL);
}
