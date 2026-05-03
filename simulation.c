#include "includes/philosopher.h"

static size_t string_len(const char *s)
{
	size_t n = 0;

	while (s && s[n])
		n++;
	return (n);
}

static int init_global_mutexes(t_rules *rules)
{
	if (pthread_mutex_init(&rules->print_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&rules->stop_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&rules->print_lock);
		return (-1);
	}
	if (pthread_mutex_init(&rules->done_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&rules->print_lock);
		pthread_mutex_destroy(&rules->stop_lock);
		return (-1);
	}
	return (0);
}

static void destroy_fork_mutexes(t_mutex *forks, int count)
{
	for (int i = 0; i < count; i++)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
}

static t_mutex *allocate_fork_mutexes(int count)
{
	t_mutex *forks;

	forks = malloc(sizeof(t_mutex) * (size_t)count);
	if (!forks)
		return (NULL);
	for (int i = 0; i < count; i++)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			destroy_fork_mutexes(forks, i);
			return (NULL);
		}
	}
	return (forks);
}

static int init_philo_meal_mutexes(t_philo *philos, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (pthread_mutex_init(&philos[i].meal_lock, NULL) != 0)
		{
			for (int j = 0; j < i; j++)
				pthread_mutex_destroy(&philos[j].meal_lock);
			return (-1);
		}
	}
	return (0);
}

static t_philo *allocate_philosophers(t_rules *rules, int count)
{
	t_philo *philos;

	philos = malloc(sizeof(t_philo) * (size_t)count);
	if (!philos)
		return (NULL);
	for (int i = 0; i < count; i++)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % count;
		philos[i].last_meal = rules->start_time;
		philos[i].meals_eaten = 0;
		philos[i].rules = rules;
	}
	if (init_philo_meal_mutexes(philos, count) != 0)
	{
		free(philos);
		return (NULL);
	}
	return (philos);
}

int simulation_init(t_rules *rules, int argc, char **argv)
{
	rules->nb_philo = (int)parse_long(argv[1]);
	rules->time_die = (size_t)parse_long(argv[2]);
	rules->time_eat = (size_t)parse_long(argv[3]);
	rules->time_sleep = (size_t)parse_long(argv[4]);
	if (argc == 6)
		rules->must_eat = (int)parse_long(argv[5]);
	else
		rules->must_eat = -1;
	rules->stop = 0;
	rules->full = 0;
	rules->start_time = now_ms();
	rules->forks = allocate_fork_mutexes(rules->nb_philo);
	if (!rules->forks)
		return (-1);
	rules->philos = allocate_philosophers(rules, rules->nb_philo);
	if (!rules->philos)
	{
		destroy_fork_mutexes(rules->forks, rules->nb_philo);
		rules->forks = NULL;
		return (-1);
	}
	if (init_global_mutexes(rules) != 0)
	{
		for (int i = 0; i < rules->nb_philo; i++)
			pthread_mutex_destroy(&rules->philos[i].meal_lock);
		free(rules->philos);
		rules->philos = NULL;
		destroy_fork_mutexes(rules->forks, rules->nb_philo);
		rules->forks = NULL;
		return (-1);
	}
	return (0);
}

static void free_fork_array(t_rules *rules)
{
	int n;

	if (!rules->forks)
		return;
	n = rules->nb_philo;
	for (int i = 0; i < n; i++)
		pthread_mutex_destroy(&rules->forks[i]);
	free(rules->forks);
	rules->forks = NULL;
}

static void free_philosophers(t_rules *rules)
{
	int n;

	if (!rules->philos)
		return;
	n = rules->nb_philo;
	for (int i = 0; i < n; i++)
		pthread_mutex_destroy(&rules->philos[i].meal_lock);
	free(rules->philos);
	rules->philos = NULL;
}

void simulation_destroy(t_rules *rules)
{
	free_fork_array(rules);
	free_philosophers(rules);
	pthread_mutex_destroy(&rules->print_lock);
	pthread_mutex_destroy(&rules->stop_lock);
	pthread_mutex_destroy(&rules->done_lock);
}

int print_error(const char *text)
{
	size_t len = string_len(text);

	write(2, "Error: ", 7);
	write(2, text, len);
	write(2, "\n", 1);
	return (1);
}

int exit_after_partial_init(t_rules *rules, const char *msg)
{
	if (rules->forks)
		free_fork_array(rules);
	if (rules->philos)
		free_philosophers(rules);
	return (print_error(msg));
}

int exit_after_failed_threads(t_rules *rules, const char *msg)
{
	simulation_destroy(rules);
	return (print_error(msg));
}

int get_stop(t_rules *rules)
{
	int v;

	pthread_mutex_lock(&rules->stop_lock);
	v = rules->stop;
	pthread_mutex_unlock(&rules->stop_lock);
	return (v);
}

void set_stop(t_rules *rules)
{
	pthread_mutex_lock(&rules->stop_lock);
	rules->stop = 1;
	pthread_mutex_unlock(&rules->stop_lock);
}

int get_full(t_rules *rules)
{
	int v;

	pthread_mutex_lock(&rules->done_lock);
	v = rules->full;
	pthread_mutex_unlock(&rules->done_lock);
	return (v);
}

void set_full(t_rules *rules)
{
	pthread_mutex_lock(&rules->done_lock);
	rules->full = 1;
	pthread_mutex_unlock(&rules->done_lock);
}

void *death_monitor_routine(void *arg)
{
	t_rules *rules = (t_rules *)arg;

	while (!get_stop(rules))
	{
		for (int i = 0; i < rules->nb_philo; i++)
		{
			size_t since_meal;

			pthread_mutex_lock(&rules->philos[i].meal_lock);
			since_meal = now_ms() - rules->philos[i].last_meal;
			pthread_mutex_unlock(&rules->philos[i].meal_lock);
			if (since_meal > rules->time_die)
			{
				if (!get_full(rules))
					print_philo_line(&rules->philos[i], "died");
				set_stop(rules);
			}
		}
		usleep(100);
	}
	return (NULL);
}

void *meal_monitor_routine(void *arg)
{
	t_rules *rules = (t_rules *)arg;

	while (!get_stop(rules) && !get_full(rules))
	{
		int completed = 0;

		for (int i = 0; i < rules->nb_philo; i++)
		{
			pthread_mutex_lock(&rules->philos[i].meal_lock);
			if (rules->philos[i].meals_eaten == rules->must_eat)
				completed++;
			pthread_mutex_unlock(&rules->philos[i].meal_lock);
		}
		if (rules->must_eat != -1 && completed == rules->nb_philo)
			set_full(rules);
	}
	return (NULL);
}

int try_lock_first_fork(t_rules *rules, int first)
{
	if (get_stop(rules))
		return (1);
	if (get_full(rules))
		return (1);
	pthread_mutex_lock(&rules->forks[first]);
	return (0);
}

int try_lock_second_fork(t_rules *rules, int first, int second)
{
	if (get_stop(rules))
	{
		pthread_mutex_unlock(&rules->forks[first]);
		return (1);
	}
	if (get_full(rules))
	{
		pthread_mutex_unlock(&rules->forks[first]);
		return (1);
	}
	pthread_mutex_lock(&rules->forks[second]);
	return (0);
}

int spawn_death_monitor(t_rules *rules, t_thread *monitor)
{
	if (pthread_create(monitor, NULL, death_monitor_routine, rules) != 0)
		return (-1);
	return (0);
}

int spawn_meal_monitor(t_rules *rules, t_thread *meal, t_thread *monitor)
{
	t_philo *ph = rules->philos;

	if (pthread_create(meal, NULL, meal_monitor_routine, rules) != 0)
	{
		for (int i = 0; i < rules->nb_philo; i++)
			pthread_join(ph[i].thread, NULL);
		pthread_join(*monitor, NULL);
		return (-1);
	}
	return (0);
}

int spawn_philosopher_threads(t_rules *rules, t_thread *monitor)
{
	t_philo *ph = rules->philos;

	for (int i = 0; i < rules->nb_philo; i++)
	{
		if (pthread_create(&ph[i].thread, NULL, philosopher_routine,
				&ph[i]) != 0)
		{
			for (int j = 0; j < i; j++)
				pthread_join(ph[j].thread, NULL);
			pthread_join(*monitor, NULL);
			return (-1);
		}
	}
	return (0);
}

void join_all_threads(t_rules *rules, t_thread *meal, t_thread *monitor)
{
	t_philo *ph = rules->philos;

	for (int i = 0; i < rules->nb_philo; i++)
		pthread_join(ph[i].thread, NULL);
	pthread_join(*meal, NULL);
	pthread_join(*monitor, NULL);
}
