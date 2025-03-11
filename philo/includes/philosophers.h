/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:51:13 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/11 05:39:43 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>

# define MAX_PHILO 200

typedef pthread_mutex_t t_mutex;
typedef pthread_t t_thread;
typedef struct timeval t_timeval;
typedef struct	s_fork
{
	int id;
	t_mutex fork;
}	t_fork;

typedef struct	s_rule
{
	t_mutex	write_lock;
	t_mutex	meal_lock;
	t_mutex	dead_lock;
	sem_t	cycle_fork;
	sem_t	cycle_meal;
}	t_rule;

typedef struct	s_philo
{
	int			id;
	int			size;
	int			meal_to_eat;
	int			meal_eaten;
	int			*is_alive;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	size_t		time_last_meal;
	size_t		time_born;
	t_thread	thread;
	t_rule		*rules;
	t_fork		*fork_l;
	t_fork		*fork_r;
}	t_philo;

typedef struct	s_table
{
	t_fork *froks;
	t_rule *rules;
	t_philo *philos;
}	t_table;

t_fork	*ft_init_forks(int size);
t_rule	*ft_init_rules(int size);
t_philo	*ft_init_philos(t_fork *forks, t_rule *rules, char *argv[], int size);
t_table	*ft_init_table(t_fork *forks, t_rule *rules, t_philo *philos);
int		ft_exit(t_table *table);
long	ft_atol(const char *nptr);
int		ft_set_table(t_table *table, int size);
int	ft_print_action(t_philo *philo, char *str);
size_t	get_current_time(void);
int	ft_usleep(size_t m_sec);

#endif
