/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:24 by tsomacha          #+#    #+#             */
/*   Updated: 2025/02/28 23:58:04 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_start(long *data, int size)
{
	int				count;
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	count = 0;
	while (count < size)
	{
		printf("%ld\n", data[count]);
		count++;
	}
	printf("Seconds since 1/1/1970: %lu\n", tv.tv_sec);
	printf("Microseconds: %ld\n", tv.tv_usec);
	printf("Minutes west of Greenwich: %d\n", tz.tz_minuteswest);
	printf("Daylight Saving Time adjustment: %d\n", tz.tz_dsttime);
}
