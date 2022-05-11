/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:52:57 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/11 00:09:22 by Loui :)          ###   ########.fr       */
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

static void	mini_philo_print(int id, long timestamp, \
				int msg_categorie, t_philo *philo)
{
	if (msg_categorie == 4)
	{
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("%07li philo %d is dead\n", timestamp, id);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
	if (msg_categorie == 5)
	{
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("All philosophers have eaten\n");
		pthread_mutex_unlock(&philo->vars->print_mutex);
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
			mini_philo_print(0, 0, 5, philo);
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
		death = philo->vars->grim_reaper - 1;
		pthread_mutex_unlock(&philo->vars->grim_reaper_mutex);
		if (death == HERE)
			mini_philo_print(philo->id, current_time(philo), 4, philo);
		kill_them_all(philo);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->eat_time_mutex);
		return (0);
	}
}
