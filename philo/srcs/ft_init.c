/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 06:30:11 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/10 00:06:07 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*ft_init_forks(int size)
{
	t_fork	*forks;
	int		count;

	count = 0;
	forks = malloc(sizeof(t_fork) * size);
	if (!forks)
		return (NULL);
	while (count < size)
	{
		forks[count].id = count + 1;
		count++;
	}
	return (forks);
}

t_rule	*ft_init_rules(int size)
{
	t_rule	*rules;

	rules = malloc(sizeof(t_rule));
	if (!rules)
		return (NULL);
	pthread_mutex_init(&rules->dead_lock, NULL);
	pthread_mutex_init(&rules->meal_lock, NULL);
	pthread_mutex_init(&rules->write_lock, NULL);
	sem_init(&rules->cycle_fork, 0, size - 1);
	sem_init(&rules->cycel_meal, 0, 1);
	return (rules);
}

static int	ft_set_param(t_philo *philo, char *argv[])
{
	philo->time_die = ft_atol(argv[2]);
	philo->time_eat = ft_atol(argv[3]);
	philo->time_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->meal_to_eat = ft_atol(argv[5]);
	else
		philo->meal_to_eat = -1;
	return (1);
}

t_philo	*ft_init_philos(t_fork *forks, t_rule *rules, char *argv[], int size)
{
	t_philo	*philos;
	int		count;

	count = 0;
	philos = malloc(sizeof(t_philo) * size);
	if (!philos || !forks || !rules)
		return (NULL);
	while (count < size)
	{
		philos[count].id = count + 1;
		philos[count].size = size;
		ft_set_param(&philos[count], argv);
		philos[count].fork_l = &forks[count];
		if (count == (size -1))
			philos[count].fork_r = &forks[0];
		else
			philos[count].fork_r = &forks[count + 1];
		philos[count].rules = rules;
		count++;
	}
	return (philos);
}

t_table	*ft_init_table(t_fork *forks, t_rule *rules, t_philo *philos)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table || !forks || !rules || !philos)
		return (NULL);
	table->froks = forks;
	table->philos = philos;
	table->rules = rules;
	return (table);
}
