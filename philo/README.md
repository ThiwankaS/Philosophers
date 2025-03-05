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

```C
bool ft_validate_args(int argc, char *argv[])
```
### checking the arguments and validate
- maximum no of philosophers program allowed is 200
	```C
	#define MAX_PHILO 200 //Decalared in the philosopher.h file
	```
- arguments should be positive integers
- number of arguments sholud be either 5 or 6 (including the name of the porgram)








