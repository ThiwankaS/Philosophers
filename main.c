/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:58:32 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/12 06:49:08 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

/**
* Entry point of the program.
* Validates input arguments and initializes simulation rules.
* Starts monitor, philosopher, and dining threads in order.
* On failure at any step, performs cleanup and returns with an error.
* Waits for all threads to finish before performing final cleanup.
*/
int	main(int argc, char **argv)
{
	t_thread	monitor;
	t_thread	meal;
	t_rules		rules;

	if (argc == 5 || argc == 6)
	{
		if (ft_is_valid(argv, argc))
		{
			if (init_rules(&rules, argc, argv))
				return (exit_err(&rules, "rules initiating fails!"));
			if (init_life(&rules, &monitor))
				return (exit_clr(&rules, "life thread creating fails!"));
			if (init_phio_routines(&rules, &monitor))
				return (exit_clr(&rules, "routine thread creating fails!"));
			if (init_dinning(&rules, &meal, &monitor))
				return (exit_clr(&rules, "dinning thread creating fails!"));
			join_all(&rules, &meal, &monitor);
			ft_cleanup(&rules);
		}
		else
			return (ft_error("Invalid arguments!"));
	}
	else
		return (ft_error(ERROR));
	return (0);
}
