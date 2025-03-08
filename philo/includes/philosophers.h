/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:51:13 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/08 06:27:28 by tsomacha         ###   ########.fr       */
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

# define MAX_PHILO 200

typedef pthread_t		t_id;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;


typedef struct s_mutexes
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_mutex	*write_lock;
	t_mutex	*meal_lock;
}	t_mutexes;

typedef struct s_times
{
	size_t	die;
	size_t	eat;
	size_t	sleep;
	size_t	last_meal;
	size_t	born_time;
}	t_times;

typedef struct s_philo
{
	int			id;
	int			must_eat;
	int			meals_eaten;
	int			philo_count;
	t_id		thread_id;
	t_times		times;
	t_mutexes	mutexes;
}	t_philo;

typedef struct s_table
{
	t_mutex	*forks;
	t_philo	*philos;
	t_mutex	meal_lock;
	t_mutex	write_lock;
}	t_table;

int		ft_init_philos(t_table *tb, t_philo *ph, t_mutex *fk, char **argv);
int		ft_init_forks(t_table *table, t_mutex *forks, int size);
void	*obsorver(void *ptr);
void	philo_routine(t_philo *philo);
void	*start_simulation(void *ptr);
int		ft_launcher(t_table *table, int size);
void	error_message(char *text, int signal);
void	destroy_all(t_table *engine, char *str, int count, int signal);
void	print_action(t_philo *philo, char *action);
void	ft_usleep(size_t mls);
int		ft_error(char *str);
int		ft_set_table(t_table *table, t_philo *philos, t_mutex *forks);
long	ft_atoi(const char *str);
size_t	get_current_time(void);
size_t	ft_strlen(const char *str);
bool	is_all_eat(t_philo *philos);
bool	ft_validate_args(int argc, char *argv[]);
void	think(t_philo *philo);

#endif
