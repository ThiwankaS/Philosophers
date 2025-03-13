/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 04:30:02 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/13 07:33:34 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_destroy(t_table *table, int size)
{
	int count;
	t_mutex *mutex;

	count = 0;
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->write_lock);
	sem_destroy(&table->cycel);
	while (count < size)
	{
		mutex = &table->froks[count].fork;
		pthread_mutex_destroy(mutex);
		count++;
	}
	return (1);
}

int	ft_exit(t_table *table)
{
	if (!table)
		return (0);
	if (table->froks)
		free(table->froks);
	if (table->philos)
		free(table->philos);
	return (1);
}
