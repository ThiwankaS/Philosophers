#include "philosophers.h"

void *f1(void *arg)
{
	int *iptr = (int *)arg;
	for(int i = 0; i < 5; i++)
	{
		sleep(1);
		printf("My   turn {%d}!\n", i);
		(*iptr)++;
	}
	return ((void *)iptr);
}

void *f2()
{
	for(int i = 0;i < 3; i++)
	{
		sleep(1);
		printf("Your turn {%d}!\n", i);
	}
	return (NULL);
}

int main (void)
{
	pthread_t thread;
	int count = 5;
	int *ptr;

	pthread_create(&thread, NULL, f1, &count);
	f2();
	pthread_join(thread, (void *)&ptr);
	printf("Return value : %d\n", *ptr);
	return (0);
}
