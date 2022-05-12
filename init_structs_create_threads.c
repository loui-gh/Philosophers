/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_create_threads.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 08:33:25 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/12 00:13:57 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_vars(t_vars *vars, char *argv[])
{
	vars->nr_philos = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	vars->grim_reaper = 2;
	if (argv[5])
		vars->meal_limit = ft_atoi(argv[5]);
	else
		vars->meal_limit = -1;
	vars->start_time = get_time();
	pthread_mutex_init(&vars->grim_mutex, NULL);
	pthread_mutex_init(&vars->print_mutex, NULL);
}

void	ft_init_r_fork_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->vars->nr_philos)
	{
		philo[i].ptr_mutex = &philo[i].r_philos->l_fork_mutex;
		i++;
	}
}

void	ft_init_philos(t_philo *philo, t_vars *vars, int nr_philos)
{
	int		i;

	i = 0;
	while (i < nr_philos)
	{
		philo[i].id = i + 1;
		philo[i].vars = vars;
		philo[i].r_philos = &philo[(i + nr_philos - 1) % nr_philos];
		philo[i].l_philos = &philo[(i + 1) % nr_philos];
		philo[i].l_fork = ON_THE_TABLE;
		philo[i].forks_in_hand = 0;
		philo[i].vars->meal_limit = vars->meal_limit;
		philo[i].start_eat_time = 0;

		pthread_mutex_init(&philo[i].l_fork_mutex, NULL);
		pthread_mutex_init(&philo[i].nr_forks_mutex, NULL);
		pthread_mutex_init(&philo[i].nr_meals_mutex, NULL);
		pthread_mutex_init(&philo[i].eat_time_mutex, NULL);

		i++;
	}
	ft_init_r_fork_mutex(philo);
}

int	ft_create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->vars->nr_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) \
		!= 0)
		{
			ft_write("Failed to create thread\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < philo->vars->nr_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
