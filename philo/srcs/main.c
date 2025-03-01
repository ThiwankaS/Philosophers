/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:53:33 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/01 21:58:05 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int balance = 0;
pthread_mutex_t mutex;

void wrtite_balance(int new_balance)
{
	usleep(250000);
	balance = new_balance;
}

int read_balance(void)
{
	usleep(250000);
	return balance;
}

void *deposit(void *amount)
{
	pthread_mutex_lock(&mutex);

	int account_balance = read_balance();
	account_balance = account_balance + *((int *)amount);
	wrtite_balance(account_balance);

	pthread_mutex_unlock(&mutex);
	return NULL;
}

int	main(void)
{
	int before = read_balance();
	printf("before : %d\n", before);

	pthread_t thread1;
	pthread_t thread2;

	pthread_mutex_init(&mutex, NULL);

	int deposit1 = 300;
	int deposit2 = 200;

	pthread_create(&thread1, NULL, deposit, (void *) &deposit1);
	pthread_create(&thread2, NULL, deposit, (void *) &deposit2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&mutex);

	int after = read_balance();
	printf("after : %d\n", after);
	return (0);
}
