/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:02:52 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/27 18:56:17 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

/*MAIN ARGS:
arg[1] nr_philos
arg[2] time_die --length of time philo can go w/o eating
arg[3] time_eat -- eating time, need to hold two forks for this one
arg[4] time_sleep -- sleep occurs right after eating, first put down forks
arg[5] (*optional) nr_times_eat -- if all philos have eaten at least X nr of times, simulation stops
Otherwise sim stops when ONE philo dies
*/
//GOAL: create a program that simulates the behaviour of a philosopher eating and thinking hahaha
//ATTEMPT #1: PASS THE ID AND STATUS OF PHILOSOPHERS AS A STRUCT
//A philosopher is represented by a thread. Each philosopher has a unique id & status 


//Philosopher status: 1 - eating, 2 - sleeping, 3 - thinking

//HERE: Create 10 threads, each taking a UNIQUE prime from the primes array above
//TRANSLATION TO PHILOSOPHERS: Take each philo and assign her status randomly

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}

	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}


void* routine(void *arg) 
{
	usleep(1);
	t_philo *philo = (t_table *)arg;
	int id = philo->id;
	// printf("id #%d\n", id);
	//eat think sleep inside
	//int a = table->philo->id;//this is the 
	pthread_mutex_lock(philo->table->mutex);
	//printf("from init philo %d\n", table->philo[i]->id);
	ft_write(id);//Is it right if it's in order?
	pthread_mutex_unlock(philo->table->mutex);
	return (0);
}

void	ft_init_her(t_table *table, int i)
{
 		philo[i]->thread = malloc(sizeof(pthread_t));
		if (i == 0)
			table->philo[i].id = 55;
		else
			table->philo[i].id = i + 1;
		table->philo[i].status = 0; //Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping -- create a mutex lock for that

		printf("init id == %d\n", table->philo[i].id);
}


int main(int argc, char* argv[]) 
{
	if (ft_handle_input_errors(argc, argv) != 0)
		return (0);

	t_philo	*philo;
	//t_philo *philo_struct;

	ft_init_table(argc, argv, philo);

	table.mutex = malloc(sizeof(pthread_mutex_t));//source of orig erre??
	pthread_mutex_init(table.mutex, NULL);//mutex is *ptr, so don't need ampersand
	philo = malloc(sizeof(t_philo) * table.number_of_philosophers);
	//philo_struct = (t_philo *)malloc(sizeof(t_philo) * table.number_of_philosophers);//each philo is a struct
	//philo array ^^ DBL-UP

// philo = NULL;
	int i = 0;
	while ( i < table.number_of_philosophers) 
	{
		// philo[i].thread = malloc(sizeof(pthread_t));
		// table.philo[i].id = i+1;
		// table.philo[i].status = 0; //Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping -- create a mutex lock for that
		ft_init_her(&table, i);
		//if (pthread_create(philo_struct[i].thread, NULL, &routine, &table) != 0) //mistake is two dif structs
		if (pthread_create(table.philo[i].thread, NULL, &routine, &table) != 0)
		{ // ^^ got to pass thru philo[i] to get access to specific values, like id, in routine
			perror("Failed to create thread");
			return 1; //th + i same as th[i]
   		}

		i++;
	}
	i = 0;
	while (i < table.number_of_philosophers)
	{
		if (pthread_join(*(table.philo[i].thread), NULL) != 0) //deref ptr here
		{
			return 2;
		}
		i++;
	}
	pthread_mutex_destroy(table.mutex);
	return 0;
}