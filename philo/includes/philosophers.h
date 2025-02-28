#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	bool	fork_in_hand;
	char	*state;
} t_philosopher;

typedef struct s_timeval
{
	time_t tv_sec;
	suseconds_t tv_usec;
} t_timeval;

typedef struct s_timezone
{
	int tz_minuteswest;
	int tz_dsttime;
} t_timezone;

int		ft_error(void);
long	ft_atol(const char *nptr);
void	ft_start(long *data, int size);

#endif
