/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:33 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/16 23:41:41 by tsomacha         ###   ########.fr       */
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
		if (ft_is_valid(argv, argc))
		{
			size = ft_atol(argv[1]);
			forks = ft_init_forks(size);
			philos = ft_init_philos(forks, &table, argv, size);
			ft_init_table(&table);
			table.froks = forks;
			table.philos = philos;
			ft_set_table(&table, size);
			ft_destroy(&table, size);
			ft_exit(&table);
		}
	}
	else
		ft_error("Incorrect no of arguments");
	return (0);
}
