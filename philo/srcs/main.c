/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:33 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/09 23:57:44 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	int		size;
	t_fork	*forks;
	t_rule	*ruels;
	t_philo	*philos;
	t_table	*table;

	if (argc >= 5)
	{
		size = ft_atol(argv[1]);
		ruels = ft_init_rules(size);
		forks = ft_init_forks(size);
		philos = ft_init_philos(forks, ruels, argv, size);
		table = ft_init_table(forks, ruels, philos);
		ft_set_table(table, size);
		ft_exit(table);
	}
	return (0);
}
