/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:02:52 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/27 22:57:16 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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


/*this produces unique values from this array. How can I get routine to produce unique values
from a struct?
PROBLEM: create x amount of threads, each with an id and status for the philosopher*/



// void* routine(void* arg) {
//     sleep(1);
//     int index = *(int*)arg;
//     printf("%d ", primes[index]);
//     free(arg);
// 	return (0);
// }

// void	ft_init_her(t_philo *ptr, int i)
// {
//  		ptr[i]->thread = malloc(sizeof(pthread_t));
// 		if (i == 0)
// 			table->philo[i].id = 55;
// 		else
// 			table->philo[i].id = i + 1;
// 		table->philo[i].status = 0; //Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping -- create a mutex lock for that

// 		printf("init id == %d\n", table->philo[i].id);
// }

int	main(int argc, char* argv[])
{

	//t_philo	*philo;
	//t_philo *philo_struct;
	argc++;
	int nr_philos = ft_atoi(argv[1]);
	printf("nr_philos == %d\n", nr_philos);

	return 0;
}
//PHILO STATUS IDEA in routine

	// while (1)
	// {
	// 	if (philo->status == 1)
	// 	{
	// 		ft_write("Philosopher ");
	// 		ft_write(ft_itoa(philo->id));
	// 		ft_write(" is eating\n");
	// 		sleep(1);
	// 	}
	// 	else if (philo->status == 2)
	// 	{
	// 		ft_write("Philosopher ");
	// 		ft_write(ft_itoa(philo->id));
	// 		ft_write(" is sleeping\n");
	// 		sleep(1);
	// 	}
	// 	else if (philo->status == 3)
	// 	{
	// 		ft_write("Philosopher ");
	// 		ft_write(ft_itoa(philo->id));
	// 		ft_write(" is thinking\n");
	// 		sleep(1);
	// 	}
	// }