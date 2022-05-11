/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:52:57 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/10 15:15:16 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_them_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->vars->nr_philos)
	{
		pthread_mutex_lock(&philo->doa_mutex);
		philo->d_o_a = DEAD;
		pthread_mutex_unlock(&philo->doa_mutex);
		i++;
		philo = philo->l_philos;
	}
}

void	ft_check_meals(t_philo *philo)
{
	int	i;
	int	j;
	int	death;

	i = 0;
	j = 0;
	while (i < philo->vars->nr_philos)
	{
		if (philo->nr_meals >= philo->vars->meal_limit)
			j++;
		philo = philo->l_philos;
		i++;
	}
	if (j == i)
	{
		pthread_mutex_lock(&philo->vars->grim_reaper_mutex);
		philo->vars->grim_reaper--;
		death = philo->vars->grim_reaper;
		pthread_mutex_unlock(&philo->vars->grim_reaper_mutex);
		if (death == HERE)
			philo_print(philo->id, current_time(philo), 4, philo);
		kill_them_all(philo);
	}
}

int	ft_survival_check(t_philo *philo)
{
	int	death;

	pthread_mutex_lock(&philo->eat_time_mutex);
	if ((current_time(philo) - philo->start_eat_time) \
			>= philo->vars->time_to_die)
	{
		pthread_mutex_unlock(&philo->eat_time_mutex);
		pthread_mutex_lock(&philo->doa_mutex);
		philo->d_o_a = DEAD;
		pthread_mutex_unlock(&philo->doa_mutex);
		pthread_mutex_lock(&philo->vars->grim_reaper_mutex);
		philo->vars->grim_reaper--;
		death = philo->vars->grim_reaper;
		pthread_mutex_unlock(&philo->vars->grim_reaper_mutex);
		if (death == HERE)
			philo_print(philo->id, current_time(philo), 4, philo);
		kill_them_all(philo);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->eat_time_mutex);
		return (0);
	}
}
