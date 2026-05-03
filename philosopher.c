#include "includes/philosopher.h"

static void print_event(t_philo *philo, const char *msg)
{
	size_t elapsed = now_ms() - philo->rules->start_time;

	printf("%zu %d %s\n", elapsed, philo->id, msg);
}

size_t now_ms(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((size_t)tv.tv_sec * 1000 + (size_t)tv.tv_usec / 1000);
}

void sleep_ms(size_t ms, t_rules *rules)
{
	size_t start = now_ms();

	while (now_ms() - start < ms && !get_stop(rules))
		usleep(500);
}

void print_philo_line(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->rules->print_lock);
	if (!get_stop(philo->rules))
		print_event(philo, msg);
	pthread_mutex_unlock(&philo->rules->print_lock);
}

static void fork_pick_order(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

static void lone_philosopher(t_philo *philo)
{
	t_rules *rules = philo->rules;
	int fork_idx = philo->left_fork;

	pthread_mutex_lock(&rules->forks[fork_idx]);
	print_philo_line(philo, "has taken a fork");
	pthread_mutex_unlock(&rules->forks[fork_idx]);
	sleep_ms(rules->time_die, rules);
	print_philo_line(philo, "died");
	set_stop(rules);
}

static void think(t_philo *philo)
{
	t_rules *rules = philo->rules;
	int think_time;

	if (get_stop(rules) || get_full(rules))
		return;
	print_philo_line(philo, "is thinking");
	think_time = (int)(rules->time_die - rules->time_sleep - rules->time_eat
		- 10);
	if (think_time > 0)
		sleep_ms((size_t)think_time, rules);
}

static void rest(t_philo *philo)
{
	t_rules *rules = philo->rules;

	if (get_stop(rules))
		return;
	print_philo_line(philo, "is sleeping");
	sleep_ms(rules->time_sleep, rules);
}

static void eat(t_philo *philo)
{
	int first;
	int second;
	t_rules *rules = philo->rules;
	size_t t;

	fork_pick_order(philo, &first, &second);
	if (try_lock_first_fork(rules, first))
		return;
	print_philo_line(philo, "has taken a fork");
	if (try_lock_second_fork(rules, first, second))
		return;
	print_philo_line(philo, "has taken a fork");
	t = now_ms();
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = t;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_philo_line(philo, "is eating");
	sleep_ms(rules->time_eat, rules);
	pthread_mutex_unlock(&rules->forks[second]);
	pthread_mutex_unlock(&rules->forks[first]);
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_rules *rules = philo->rules;

	if (rules->nb_philo == 1)
	{
		lone_philosopher(philo);
		return (NULL);
	}
	if (philo->id % 2)
	{
		print_philo_line(philo, "is thinking");
		sleep_ms(rules->time_eat, rules);
	}
	while (!get_stop(rules) && !get_full(rules))
	{
		eat(philo);
		rest(philo);
		think(philo);
	}
	return (NULL);
}
