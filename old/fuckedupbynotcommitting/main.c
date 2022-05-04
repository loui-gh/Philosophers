/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:24:22 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/28 23:03:26 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos(t_philo *philo, int i)
{
	//ptr[i]->thread = malloc(sizeof(pthread_t));
	philo[i].id = i + 1;
	//Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping -- create a mutex lock for that
}

void	*ft_routine(void *arg)
{
	t_philo *philo;
	t_vars	vars;
	philo = (t_philo *)arg;
	///philo->mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_lock(&vars.mutex);
	ft_write("Hello from thread id ");
	ft_putnbr(philo->id);
	ft_write("\n");
	//printf("Hello from thread \n");
	ft_write("Ending thread\n");
	pthread_mutex_unlock(&vars.mutex);
	return (0);
}

int	main(int argc, char *argv[])
{
	int		nr_philos;
	int		i;
	t_philo	*philo;
	t_vars	vars;

	
	
	if (ft_handle_input_errors(argc, argv) != 0)
		return (0);
	nr_philos = ft_atoi(argv[1]);
	
	philo = malloc(sizeof(t_philo) * nr_philos);

	

	pthread_mutex_init(&vars.mutex, NULL);

	//philo->mutex = malloc(sizeof(pthread_mutex_t) * nr_philos);//it is essential to malloc mutexes. It is a big fucking variable??
	//init philos as an array of structures
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
	return (0);
}



