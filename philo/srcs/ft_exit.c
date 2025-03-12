/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 04:30:02 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/12 07:51:49 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_destroy(t_table *table, int size)
{
	int count;
	t_mutex *mutex;
	t_philo *philo;

	count = 0;
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->write_lock);
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
