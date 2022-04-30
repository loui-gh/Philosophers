/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:35:49 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/30 21:35:06 by Loui :)          ###   ########.fr       */
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
	//t_vars vars;
	philo = (t_philo *)arg;
	hello(philo->id, philo->index);
	// pthread_mutex_lock(&vars.l_mutex);
	// printf("Philo %d created, neighbour should be %d\n", philo->id, philo->l_philos->id);
	// pthread_mutex_unlock(&vars.l_mutex);
	
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
	
	//philo->vars->mutex = malloc(sizeof(pthread_mutex_t) * nr_philos);
	pthread_mutex_init(&vars.l_mutex, NULL);
	pthread_mutex_init(&vars.l_mutex, NULL);


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
	pthread_mutex_destroy(&vars.l_mutex);
	free(philo);
	i = 0;

	
	return (0);
}
