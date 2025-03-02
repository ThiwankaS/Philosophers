/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:24 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/02 04:13:22 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_forks *ft_init_forks(int size)
{
	int count = 0;
	t_forks *forks = malloc(sizeof(t_forks) * size);
	while(count < size)
	{
		forks[count].id = count + 1;
		forks[count].is_taken = false;
		count++;
	}
	return (forks);
}

t_philosopher *ft_init_philo(int size, t_forks *forks)
{
	int count = 0;
	t_philosopher *philo = malloc(sizeof(t_philosopher) * size);
	while(count < size)
	{
		philo[count].id = count + 1;
		philo[count].is_alive = true;
		philo[count].meals_eaten = 0;
		philo[count].fork_l = &forks[count];
		philo[count].fork_r = NULL;
		count++;
	}
	return (philo);
}
