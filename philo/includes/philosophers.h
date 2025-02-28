/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:51:13 by tsomacha          #+#    #+#             */
/*   Updated: 2025/02/28 23:53:39 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_philosopher
{
	bool	fork_in_hand;
	char	*state;
}	t_philosopher;

int		ft_error(void);
long	ft_atol(const char *nptr);
void	ft_start(long *data, int size);

#endif
