/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:01:49 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/16 23:08:18 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_is_valid(char *argv[], int argc)
{
	long	arg;
	int		count;

	arg = ft_atol(argv[1]);
	if (arg < 1 || arg > MAX_PHILO)
		return (ft_error("Invalid input <no_of_philosophers>"));
	count = 2;
	while (count < argc)
	{
		arg = ft_atol(argv[count]);
		if (arg < 0 || arg > INT_MAX)
			return (ft_error("Invalid input"));
		count++;
	}
	return (1);
}
