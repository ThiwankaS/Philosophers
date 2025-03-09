/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 06:30:11 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/09 22:05:27 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork *ft_init_forks(int size)
{
	t_fork *forks;
	int	count;

	count = 0;
	forks = malloc(sizeof(t_fork) * size);
	if (!forks)
		return (NULL);
	while(count < size)
	{
		forks[count].id = count  + 1;
		count++;
	}
	return (forks);
}
t_rule *ft_init_rules(void)
{
	t_rule *rules;
	rules = malloc(sizeof(t_rule));
	if (!rules)
		return (NULL);
	pthread_mutex_init(&rules->dead_lock, NULL);
	pthread_mutex_init(&rules->meal_lock, NULL);
	pthread_mutex_init(&rules->write_lock, NULL);
	return (rules);
}
t_philo *ft_init_philos(t_fork *forks, t_rule *rules, char *argv[], int size)
{
	t_philo *philos;
	int count;

	count = 0;
	philos = malloc(sizeof(t_philo) * size);
	if (!philos || !forks || !rules)
		return (NULL);
	while (count < size)
	{
		philos[count].id = count + 1;
		philos[count].size = size;
		philos[count].time_die = ft_atol(argv[2]);
		philos[count].time_eat = ft_atol(argv[3]);
		philos[count].time_sleep = ft_atol(argv[4]);
		if(argv[5])
			philos[count].meal_to_eat = ft_atol(argv[5]);
		else
			philos[count].meal_to_eat = -1;
		philos[count].write_lock = &rules->write_lock;
		philos[count].meal_lock = &rules->meal_lock;
		philos[count].dead_lock = &rules->dead_lock;
		philos[count].fork_l = &forks[count];
		if (count == (size -1))
			philos[count].fork_r = &forks[0];
		else
			philos[count].fork_r = &forks[count + 1];
		count++;
	}
	return (philos);
}

t_table *ft_init_table(t_fork *forks, t_rule *rules, t_philo *philos)
{
	t_table *table;
	table = malloc(sizeof(t_table));
	if (!table || !forks || !rules || !philos)
		return (NULL);
	table->froks = forks;
	table->philos = philos;
	table->rules = rules;
	return (table);
}
