/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:51:13 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/16 23:37:14 by tsomacha         ###   ########.fr       */
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

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef struct timeval	t_timeval;
typedef struct s_fork
{
	int		id;
	t_mutex	fork;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			size;
	int			meal_to_eat;
	int			meal_eaten;
	int			*is_alive;
	int			is_eating;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	size_t		time_last_meal;
	size_t		time_born;
	t_mutex		*write_lock;
	t_mutex		*meal_lock;
	t_mutex		*dead_lock;
	t_thread	thread;
	t_fork		*fork_l;
	t_fork		*fork_r;
}	t_philo;

typedef struct s_table
{
	int		is_alive;
	t_mutex	write_lock;
	t_mutex	meal_lock;
	t_mutex	dead_lock;
	t_fork	*froks;
	t_philo	*philos;
}	t_table;

t_fork	*ft_init_forks(int size);
t_philo	*ft_init_philos(t_fork *forks, t_table *table, char *argv[], int size);
int		ft_init_table(t_table *table);
long	ft_atol(const char *nptr);
int		ft_set_table(t_table *table, int size);
int		ft_destroy(t_table *table, int size);
int		is_alive(t_philo *philo);
int		ft_error(char *str);

int	ft_is_valid(char *argv[], int argc);

int	ft_sleep(t_philo *philo);
int	ft_think(t_philo *philo);
int	ft_eat(t_philo *philo);
void	*ft_sml(void *arg);

//ft_utils.c
int		ft_usleep(size_t m_sec);
int		ft_print_action(t_philo *philo, char *str);
size_t	get_current_time(void);
size_t	ft_strlen(const char *str);
int		ft_exit(t_table *table); //temporary
#endif
