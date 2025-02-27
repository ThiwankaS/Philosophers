#include "philosophers.h"

int main (int argc, char *argv[])
{
	if (argc == 5)
	{
		printf("Correct no of aguments!\n");
		printf("%s\n", argv[0]);
	}
	else if (argc == 6)
	{
		printf("Correct no of aguments with np_eat!\n");
	}
	else
		write(2,"Error\n",7);
	return (0);
}
