#include "philosophers.h"

void *f1()
{
	while(1)
	{
		sleep(1);
		printf("My turn!\n");
	}
	return (NULL);
}

void *f2()
{
	while(1)
	{
		sleep(2);
		printf("Your turn!\n");
	}
}

int main (void)
{
	pthread_t thread;

	pthread_create(&thread, NULL, f1, NULL);
	f2();
	pthread_join(thread, NULL);
	return (0);
}
