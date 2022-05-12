/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:52:57 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/12 00:22:25 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_normi_check_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->grim_mutex);
	if (philo->vars->grim_reaper != HERE)
	{
		pthread_mutex_unlock(&philo->vars->grim_mutex);

		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("All philosophers have eaten\n");
		pthread_mutex_unlock(&philo->vars->print_mutex);

		pthread_mutex_lock(&philo->vars->grim_mutex);
			philo->vars->grim_reaper = HERE;
			pthread_mutex_unlock(&philo->vars->grim_mutex);
	}
	else
		pthread_mutex_unlock(&philo->vars->grim_mutex);
}

void	ft_check_meals(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	pthread_mutex_lock(&philo->vars->grim_mutex);
	if (philo->vars->grim_reaper != HERE)
	{
		pthread_mutex_unlock(&philo->vars->grim_mutex);
		while (i < philo->vars->nr_philos)
		{
			pthread_mutex_lock(&philo->nr_meals_mutex);
			if (philo->nr_meals >= philo->vars->meal_limit)
			{
				pthread_mutex_unlock(&philo->nr_meals_mutex);
				j++;
			}
			else
				pthread_mutex_unlock(&philo->nr_meals_mutex);
			philo = philo->l_philos;
			i++;
		}
		if (j == i)
			ft_normi_check_meals(philo);
	}
	else
		pthread_mutex_unlock(&philo->vars->grim_mutex);
}

int	ft_survival_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->grim_mutex);
	if (philo->vars->grim_reaper != HERE)
	{
		pthread_mutex_unlock(&philo->vars->grim_mutex);
	
		pthread_mutex_lock(&philo->eat_time_mutex);
		if ((current_time(philo) - philo->start_eat_time) \
				>= philo->vars->time_to_die)
		{
			pthread_mutex_unlock(&philo->eat_time_mutex);
			pthread_mutex_lock(&philo->vars->grim_mutex);
			if (philo->vars->grim_reaper != HERE)
			{
				pthread_mutex_unlock(&philo->vars->grim_mutex);
				pthread_mutex_lock(&philo->vars->print_mutex);
				printf("%07li philo %d is dead\n", current_time(philo), philo->id);
				pthread_mutex_unlock(&philo->vars->print_mutex);
		
				pthread_mutex_lock(&philo->vars->grim_mutex);
				philo->vars->grim_reaper = HERE;
				pthread_mutex_unlock(&philo->vars->grim_mutex);
				return(1);
				
			}
			else
				pthread_mutex_unlock(&philo->vars->grim_mutex);
		}
		else
			pthread_mutex_unlock(&philo->eat_time_mutex);

	}
	else
		pthread_mutex_unlock(&philo->vars->grim_mutex);

	return (0);
}
