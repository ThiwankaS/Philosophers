/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:33 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/02 04:18:33 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *ft_routine(void *arg)
{
	t_philosopher philo = *((t_philosopher *)arg);
	while(philo.is_alive)
	{
		printf("philosopher %d is eating with fork %d\n", philo.id, philo.fork_l->id);
		philo.meals_eaten++;
		usleep(1000000);
		printf("philosopher %d is sleeping\n", philo.id);
		usleep(1500000);
		printf("philosopher %d is thinking\n", philo.id);
		usleep(2500000);
		printf("philosopher %d { no of meals } : %d\n", philo.id, philo.meals_eaten);
		printf("------------------------------------\n");
		usleep(1500000);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	if(argc == 2)
	{
		int size = (int)ft_atol(argv[1]);
		int count = 0;
		t_forks *forks = ft_init_forks(size);
		t_philosopher *philos = ft_init_philo(size, forks);
		while (count < size)
		{
			pthread_create(&philos[count].thread, NULL, ft_routine, &philos[count]);
			count++;
		}
		count = 0;
		while (count < size)
		{
			pthread_join(philos[count].thread, NULL);
			count++;
		}
	}
	return (0);
}
