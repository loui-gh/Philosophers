/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 08:33:25 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/02 09:38:20 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos(t_philo *philo, t_vars *vars, int nr_philos)
{
	//POSSIBLE TO WORK W/O NR_PHILOS?

	//INITIALISE PHILOS WITH PHILO[I]->VARS= & VARS
	int		i;
	i = 0;
	while (i < nr_philos)
	{
		philo[i].id = i + 1;
		philo[i].vars = vars;//make sure all philos pointing to same vars struct
		philo[i].index = i;
		philo[i].l_philos = &philo[(i + nr_philos - 1) % nr_philos];
		philo[i].r_philos = &philo[(i + 1) % nr_philos];
		philo[i].l_fork = ON_THE_TABLE;
		philo[i].r_fork = ON_THE_TABLE;

		//printf("Hello from philosopher %d, index %d\n", philo[i].id, philo[i].index);
		i++;
	}

	// PRINT TO SHOW IDs accessible from ptr.s
	// i = 0;
	// while (i < nr_philos)
	// {
	// 	printf("Philo %d created, neighbour to the left should be %d ", philo[i].id, philo[i].l_philos->id);
	// 	printf("to her right is %d\n", philo[i].r_philos->id);
	// 	i++;
	// }
}
