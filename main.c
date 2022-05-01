/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:35:49 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/01 15:27:03 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	hello(int id, int index)
{
	t_vars vars;
	pthread_mutex_lock(&vars.write);
	printf("Hello from philosopher %d, index %d\n", id, index);
	pthread_mutex_unlock(&vars.write);
}

void	*ft_routine(void *arg)
{
	t_philo *philo;
	t_vars vars;
	philo = (t_philo *)arg;
	hello(philo->id, philo->index);
	
	if (philo->l_fork == ON_THE_TABLE && philo->r_fork == ON_THE_TABLE)
	{
		pthread_mutex_lock(&vars.write);
		printf("Philosopher %d has taken a fork\n", philo->id);
		
		philo->l_fork = TAKEN;
		philo->r_fork = TAKEN;
		philo->r_philos->l_fork = TAKEN;
		philo->l_philos->r_fork = TAKEN;
		pthread_mutex_unlock(&vars.write);
		pthread_mutex_lock(&vars.eat_mutex);
		printf("Philosopher %d is eating\n", philo->id);
		usleep(vars.time_to_eat * 1000); //convert milli to micro
		philo->l_fork = ON_THE_TABLE;
		philo->r_fork = ON_THE_TABLE;
		philo->r_philos->l_fork = ON_THE_TABLE;
		philo->l_philos->r_fork = ON_THE_TABLE;
		pthread_mutex_lock(&vars.write);
		printf("Philosopher %d is sleeping\n", philo->id);
		usleep(vars.time_to_sleep * 1000); //convert milli to micro
		pthread_mutex_unlock(&vars.write);
		pthread_mutex_unlock(&vars.eat_mutex);
		
		// sleep(vars.time_to_sleep);
		// philo->l_fork = ON_THE_TABLE;
		// philo->r_fork = ON_THE_TABLE;
		
	}
	
// 	if (philo->l_fork == ON_THE_TABLE && philo->r_fork == ON_THE_TABLE)
// 	{
// 		pthread_mutex_lock(&vars.write);
// 		printf("Philosopher %d is eating\n", philo->id);
// 		pthread_mutex_unlock(&vars.write);
// 		sleep(vars.time_to_eat);
// 		pthread_mutex_lock(&vars.write);
// 		printf("Philosopher %d is sleeping\n", philo->id);
// 		pthread_mutex_unlock(&vars.write);
// 		pthread_mutex_unlock(&vars.eat_mutex);
// 		pthread_mutex_lock(&vars.write);
// 		printf("Philosopher %d is thinking\n", philo->id);
// 		pthread_mutex_unlock(&vars.write);
// 		pthread_mutex_lock(&vars.write);
// 		printf("Philosopher %d is hungry\n", philo->id);
// 		pthread_mutex_unlock(&vars.write);
// 		pthread_mutex_lock(&vars.eat_mutex);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&vars.write);
// 		printf("Philosopher %d is waiting\n", philo->id);
// 		pthread_mutex_unlock(&vars.write);
// 		pthread_mutex_unlock(&vars.eat_mutex);
// 		pthread_mutex_lock(&vars.write);
// 		printf("Philosopher %d is thinking\n", philo->id);
// 		pthread_mutex_unlock(&vars.write);
// 		pthread_mutex_lock(&vars.eat_mutex);
// 	}
	
	
	return(0);
}

int	main(int argc, char *argv[])
{
	//int		nr_philos;
	int		i;
	t_philo	*philo;
	t_vars	vars; //don't need to malloc vars or vars.l_mutex here
	
	if (ft_handle_input_errors(argc, argv) != 0)
		return (0);
	
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	vars.nr_philos = ft_atoi(argv[1]);
	vars.time_to_eat = ft_atoi(argv[3]);
	vars.time_to_sleep = ft_atoi(argv[4]);
	//need to convert this back to milliseconds for printing
	//printf("time to eat%ld\n", vars.time_to_eat);
	
	//philo->vars->mutex = malloc(sizeof(pthread_mutex_t) * nr_philos);
	pthread_mutex_init(&vars.write, NULL);
	pthread_mutex_init(&vars.eat_mutex, NULL);


	ft_init_philos(philo, vars.nr_philos);
	i = 0;
	while (i < vars.nr_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0) 
		{
			perror("Failed to create thread");
			return 1;
		}
		i++;
	}
	
	i = 0;
	while (i < vars.nr_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0) 
		{
			write(2, "5\n", 2);
			return 3;
		}
		i++;
	}

	pthread_mutex_destroy(&vars.write);
	pthread_mutex_destroy(&vars.eat_mutex);
	free(philo);
	i = 0;

	
	return (0);
}
