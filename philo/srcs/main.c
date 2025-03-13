/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:33 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/13 07:15:50 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	int		size;
	t_fork	*forks;
	t_philo	*philos;
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		size = ft_atol(argv[1]);
		forks = ft_init_forks(size);
		philos = ft_init_philos(forks, &table, argv, size);
		ft_init_table(&table, size);
		table.froks = forks;
		table.philos = philos;
		ft_set_table(&table, size);
		ft_destroy(&table, size);
		ft_exit(&table);
	}
	return (0);
}
