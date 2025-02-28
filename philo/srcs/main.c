/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:33 by tsomacha          #+#    #+#             */
/*   Updated: 2025/02/28 23:57:18 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	int		count;
	int		step;
	long	*data;

	count = 1;
	step = 0;
	if (argc == 5 || argc == 6)
	{
		data = malloc(sizeof(long) * argc);
		if (!data)
			ft_error();
		while (count < argc)
		{
			data[step] = ft_atol(argv[count]);
			count++;
			step++;
		}
		ft_start(data, argc);
	}
	else
		ft_error();
	return (0);
}
