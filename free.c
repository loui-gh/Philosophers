/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:04:29 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/06 12:08:07 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *philo, int nr_philos)
{
	//Deki had pthread_join here. What's the purpose??
	int j = 0;
	while (j < nr_philos)
	{
		pthread_mutex_destroy(&philo[j].l_fork_mutex);
		pthread_mutex_destroy(&philo[j].nr_forks_mutex);
		pthread_mutex_destroy(&philo[j].nr_meals_mutex);
		j++;
	}
	pthread_mutex_destroy(&philo->vars->print_mutex);
	pthread_mutex_destroy(&philo->vars->mutex);

	free(philo);
}