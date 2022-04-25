/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:02:52 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/25 14:25:55 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

typedef struct s_philo
{
	int		id;
	int		status;
	int		eat_count;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

//GOAL: create a program that simulates the behaviour of a philosopher eating and thinking hahaha
//ATTEMPT #1: PASS THE ID AND STATUS OF PHILOSOPHERS AS A STRUCT
//A philosopher is represented by a thread. Each philosopher has a unique id & status 

//Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping
//Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping
//Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping
//ID is just the index +1

int	main(int argc, char *argv[])
{
	if (ft_handle_input_errors(argc, argv) != 0)
		return (0);

	t_vars *vars;
	vars = malloc(sizeof(t_vars));
	ft_init_vars(argc, argv, vars);
}