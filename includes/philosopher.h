#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define USAGE_MSG \
	"Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep " \
	"[meals_per_philosopher]"

typedef pthread_t t_thread;
typedef pthread_mutex_t t_mutex;

typedef struct s_rules t_rules;

typedef struct s_philo
{
	int id;
	int left_fork;
	int right_fork;
	int meals_eaten;
	size_t last_meal;
	t_thread thread;
	t_mutex meal_lock;
	t_rules *rules;
} t_philo;

struct s_rules
{
	int nb_philo;
	int must_eat;
	int stop;
	int full;
	t_mutex *forks;
	t_mutex print_lock;
	t_mutex stop_lock;
	t_mutex done_lock;
	size_t time_die;
	size_t time_eat;
	size_t time_sleep;
	size_t start_time;
	t_philo *philos;
};

/* args.c */
long parse_long(const char *str);
int args_are_valid(int argc, char **argv);

/* simulation.c — lifecycle, monitors, thread orchestration */
int simulation_init(t_rules *rules, int argc, char **argv);
void simulation_destroy(t_rules *rules);
int print_error(const char *text);
int exit_after_partial_init(t_rules *rules, const char *msg);
int exit_after_failed_threads(t_rules *rules, const char *msg);

int get_stop(t_rules *rules);
void set_stop(t_rules *rules);
int get_full(t_rules *rules);
void set_full(t_rules *rules);

void *death_monitor_routine(void *arg);
void *meal_monitor_routine(void *arg);

int spawn_death_monitor(t_rules *rules, t_thread *monitor);
int spawn_meal_monitor(t_rules *rules, t_thread *meal, t_thread *monitor);
int spawn_philosopher_threads(t_rules *rules, t_thread *monitor);
void join_all_threads(t_rules *rules, t_thread *meal, t_thread *monitor);

int try_lock_first_fork(t_rules *rules, int first);
int try_lock_second_fork(t_rules *rules, int first, int second);

/* philosopher.c — philosopher thread + I/O helpers */
void *philosopher_routine(void *arg);

size_t now_ms(void);
void sleep_ms(size_t ms, t_rules *rules);
void print_philo_line(t_philo *philo, const char *msg);

#endif
