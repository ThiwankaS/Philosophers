/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:33 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/08 06:09:54 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	int	size;
	t_philo	*philos;
	t_mutex	*forks;
	t_table	*table;

	if (ft_validate_args(argc, argv))
	{
		size = ft_atoi(argv[1]);
		forks = malloc(sizeof(t_mutex)*size);
		philos = malloc(sizeof(t_philo)*size);
		table = malloc(sizeof(t_table));
		if(!forks || !philos || !table)
			ft_error("[ FAILD TO ALLOCATE MEMOMRY! ]\n");
		ft_set_table(table, philos, forks);
		ft_init_forks(table, forks, size);
		ft_init_philos(table, philos, forks, argv);
		ft_launcher(table, size);
		destroy_all(table, NULL, philos[0].philo_count, 0);
	}
	return (0);
}
