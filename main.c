/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:35:49 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/29 14:47:46 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_philo *philo;
	t_vars	vars;
	philo = (t_philo *)arg;
	///philo->mutex = malloc(sizeof(pthread_mutex_t));
	//usleep(3); --makes no diff to sloppy execution
	//REMEMBER: This is not a process!!
	/*only need to malloc ptrs in t_vars --according to B-dawg's code (Boris)*/
	//BORIS: dt->mutex = malloc(sizeof(pthread_mutex_t) * (ft_atoi(argv[1])));
	
	pthread_mutex_lock(&vars.mutex);
	hello(philo->id);
	pthread_mutex_unlock(&vars.mutex);
	
	
	return(0);
}

int	main(int argc, char *argv[])
{
	int		nr_philos;
	int		i;
	t_philo	*philo;
	t_vars	vars; //don't need to malloc vars or vars.mutex here
	
	if (ft_handle_input_errors(argc, argv) != 0)
		return (0);
	nr_philos = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * nr_philos);
	pthread_mutex_init(&vars.mutex, NULL);
	pthread_mutex_init(&vars.write, NULL);

	i = 0;
	while (i < nr_philos)
	{
		
		ft_init_philos(philo, i);
		//need a mutex_init for every philo?
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0) 
		{
			perror("Failed to create thread");
			return 1;
		}
		i++;
	}
	
	i = 0;
	while (i < nr_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0) 
		{
			write(2, "5\n", 2);
			return 3;
		}
		i++;
	}
	pthread_mutex_destroy(&vars.mutex);
	pthread_mutex_destroy(&vars.write);
	
	return (0);
}

void	ft_init_philos(t_philo *philo, int i)
{
	//ptr[i]->thread = malloc(sizeof(pthread_t));
	philo[i].id = i + 1;
	//Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping -- create a mutex lock for that
}
