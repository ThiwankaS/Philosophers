## Dinning Philosophers

The progrm starts following the command on the terminal, and should follow the format
```
./philo <arg1> <arg2> <arg3> <arg4> [<arg5>]
```
where

* arg1 - number_of_philosophers : The number of philosophers and also the number of forks.
* arg2 - time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
* arg3 - time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
* arg4 - time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
* arg5 - number_of_times_each_philosopher_must_eat (optional argument)
If all philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops  when any of the philosopher dies.

### checking the arguments and validate
```C
bool ft_validate_args(int argc, char *argv[])
```
- at least 1 philosopher should be initialized to run the program and maximum no of philosophers allowed is 200
	```C
	#define MAX_PHILO 200 //Decalared in the philosopher.h file
	```
- arguments should be positive integers
- number of arguments sholud be either 5 or 6 (including the name of the porgram)

Function ```ft_validate_args``` will return ```true``` in the event all the above conditions are fufilled.If one of them fails to fullfill the funtion returns ```false```

### intializing the table
```C
int ft_set_table(t_tabel *table, t_philo *philos, t_mutex *forks)
```
```ft_set_table``` will intialize the atable and table rules as described in the subject. As it gose,
- One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.

```t_mutex``` is a typedef decalerd as follows
```C
typedef pthread_mutex_t	t_mutex; //Deaclared inside philosoher.h file
```
```t_table``` and ```t_philo``` also data structures decalred inside ```philosopher.h``` file
```C
typedef struct s_table
{
	t_mutex	*forks;			//pointer to array of forks
	t_philo	*philos;		//pointer to array of philosopers
	t_mutex	meal_lock;		//
	t_mutex	write_lock;		//
}	t_table;
```
### initializing forks
```C
int ft_init_forks(t_table *table, t_mutex *forks, int size)
```
Function ```ft_init_forks``` will create ```size``` number of forks and initialized. Following is the data structure of the ```t_mutexes```.As per the subject guideline,
 - There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
 - To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.

```C
typedef struct s_mutexes
{
	t_mutex	*left_fork;		//
	t_mutex	*right_fork;	//
	t_mutex	*write_lock;	//
	t_mutex	*meal_lock;		//
}	t_mutexes;
```
### intializing philosophers
```C
int		ft_init_philos(t_table *tb, t_philo *ph, t_mutex *fk, char **argv)
```
This fucntion will intialized the data struture ```t_philo *philos``` which consist of ```arg1``` number of philosophers.
Subject dictate,
 - Each philosopher should be a thread.

```C
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
```
### starting the program
```C
int ft_start(t_philo *philos, int size)
```
Function ```ft_start``` will start the program as name suggested. In this project we are using addition theard called observer to oversee the times. In that way we can keep track of time in a more centralized way, becuase once all the treads starts to process each and every thread in independent from each other. The observer thread will check the last meal time agains the time to die and no of meals each philosphers had.











