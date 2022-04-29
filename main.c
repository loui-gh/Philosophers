/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:35:49 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/29 21:45:59 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*ft_routine(void *arg)
{
	t_philo *philo;
	t_vars	vars;
	philo = (t_philo *)arg;
	hello(philo->id);//id+1 is to the right
	//but! if philo->id == nr philos, philo to your right is 1
	
	if (philo->fork == 1 && philo[philo->id + 1]->fork == 1)
	{
		pthread_mutex_lock(&vars.mutex);
		ft_write("pick up the fucking fork!\n");
		philo->r_fork = 0;
		philo->l_fork = 0;
		philo[philo->id + 1].l_fork = 0;
		philo[philo->id + 1].r_fork = 0;
		
	}
	else
		ft_write("no forks, no food, fucker\n");
	pthread_mutex_unlock(&vars.mutex);
	/*pick up forks*/
	

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
	philo[i].fork = 1;
}
