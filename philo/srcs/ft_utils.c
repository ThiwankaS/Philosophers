/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:48:11 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/16 23:00:43 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str && str[count])
		count++;
	return (count);
}

size_t	get_current_time(void)
{
	t_timeval	time;
	size_t		m_sec;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	m_sec = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (m_sec);
}

int	ft_print_action(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->time_born;
	if (is_alive(philo))
		printf("%ld %d %s\n", time, philo->id, str);
	else
		printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
	return (0);
}

int	ft_usleep(size_t m_sec)
{
	size_t	time;

	time = get_current_time();
	while (get_current_time() - time < m_sec)
		usleep(100);
	return (1);
}

int	ft_error(char *str)
{
	int	len;
	int	res;

	res = 0;
	len = ft_strlen(str);
	res += write(2, "ERROR ! : [ ", 12);
	res += write(2, str, len);
	res += write(2, " ]\n", 3);
	return (0);
}
