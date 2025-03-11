/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:48:11 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/10 06:34:13 by tsomacha         ###   ########.fr       */
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

int	ft_exit(t_table *table)
{
	if (!table)
		return (0);
	if (table->froks)
		free(table->froks);
	if (table->rules)
		free(table->rules);
	if (table->philos)
		free(table->philos);
	free(table);
	return (1);
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

	pthread_mutex_lock(&philo->rules->write_lock);
	time = get_current_time() - philo->time_born;
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->rules->write_lock);
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

