/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:02:52 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/25 22:09:50 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

//GOAL: create a program that simulates the behaviour of a philosopher eating and thinking hahaha
//ATTEMPT #1: PASS THE ID AND STATUS OF PHILOSOPHERS AS A STRUCT
//A philosopher is represented by a thread. Each philosopher has a unique id & status 

//Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping
//Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping
//Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping
//ID is just the index +1

//HERE: Create 10 threads, each taking a UNIQUE prime from the primes array above
//TRANSLATION TO PHILOSOPHERS: Take each philo and assign her status randomly

int mails = 0;

void	ft_write()
{
	int i = 0;
	while (i < 3)
	{
		write(1, &i, 1);
		i++;
	}
}
void* routine(void *arg) 
{
	usleep(1);
	t_table *table = (t_table *)arg;
	printf("Philo %d is awake\n", table->philo->id);
	// pthread_mutex_lock(table->mutex);
	// ft_write();
	// pthread_mutex_unlock(table->mutex);
	int i;
	//eat think sleep inside 
	while(i < 10000000) 
	{
        pthread_mutex_lock(table->mutex);
        mails++;
        pthread_mutex_unlock(table->mutex);
		i++;
	}
	return (0);
}

int main(int argc, char* argv[]) 
{
	if (ft_handle_input_errors(argc, argv) != 0)
		return (0);

	t_table table;
	t_philo *philo;

	ft_init_table(argc, argv, &table);
	table.mutex = malloc(sizeof(pthread_mutex_t));//source of orig erre??
    pthread_mutex_init(table.mutex, NULL);//mutex is *ptr, so don't need ampersand

	table.philo = malloc(sizeof(t_philo) * table.number_of_philosophers);
	philo = (t_philo *)malloc(sizeof(t_philo) * table.number_of_philosophers);//each philo is a struct
	//philo array ^^
	int i;
	i = 0;
	 
//array of philos, size no. of philo
   while ( i < table.number_of_philosophers) 
   {
	   philo[i].thread = malloc(sizeof(pthread_t));
	
        if (pthread_create(philo[i].thread, NULL, &routine, &table) != 0) {
            perror("Failed to create thread");
            return 1; //th + i same as th[i]
   		}
		
		i++;
	}
	i = 0;
    while (i < table.number_of_philosophers)
	{
        if (pthread_join(*(philo[i].thread), NULL) != 0) //deref ptr here
		{
            return 2;
        }
        //printf("Philo %d has finished eating\n", i);
		i++;
    }
    pthread_mutex_destroy(table.mutex);
    return 0;
}