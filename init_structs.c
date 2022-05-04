/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 08:33:25 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/04 19:50:00 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_vars(t_vars *vars, char *argv[])
{
	vars->nr_philos = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		vars->meal_limit = ft_atoi(argv[5]);
	else
		vars->meal_limit = -1;
	pthread_mutex_init(&vars->print_mutex, NULL);
	pthread_mutex_init(&vars->read_mutex, NULL);

}

void	ft_init_philos(t_philo *philo, t_vars *vars, int nr_philos)
{
	int		i;
	i = 0;
	while (i < nr_philos)
	{
		philo[i].id = i + 1;
		philo[i].vars = vars;//make sure all philos pointing to same vars struct
		philo[i].index = i;
		philo[i].r_philos = &philo[(i + nr_philos - 1) % nr_philos];
		philo[i].l_philos = &philo[(i + 1) % nr_philos];
		philo[i].l_fork = ON_THE_TABLE;//remove one fork, add mutex

		//error could be not identifying right lady
		//philo[i].nr_meals = vars->meal_limit;
		pthread_mutex_init(&philo[i].l_fork_mutex, NULL);
		i++;
	}
	//TEST
	// i = 0;
	// while (i < nr_philos)
	// {
	// 	if (philo[i].l_fork != TAKEN && philo[i].r_philos->l_fork != TAKEN)
	// 	{
	// 		philo[i].l_fork = TAKEN;
	// 		philo[i].r_philos->l_fork = TAKEN;
	// 	}
	// 	if (philo[i].l_fork == TAKEN && philo[i].r_philos->l_fork == TAKEN)
	// 		printf("philo %d has both forks\n", philo[i].id);
	// 	i++;
	// }

//THIS CHANGES THE VALUE OF THE FORKS
	// i = 0;
	// while (i < 25)
	// {
	// 	if (philo[i].l_fork == ON_THE_TABLE && philo[i].r_philos->l_fork == ON_THE_TABLE)
	// 	{
	// 		philo[i].l_fork = TAKEN_PHILO;
	// 		philo[i].r_philos->l_fork = TAKEN_PHILO;
	// 		printf("philo %d has both forks\n", philo[i].id);
	// 	}
	// 	i++;
	// }
	// printf("end of init_structs\n");
}