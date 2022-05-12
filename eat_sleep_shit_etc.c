/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_shit_etc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:25:00 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/12 00:16:13 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	normi_ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->nr_meals_mutex);
	philo->nr_meals++;
	pthread_mutex_unlock(&philo->nr_meals_mutex);
	if (philo->vars->meal_limit > 0)
		ft_check_meals(philo);
}

static void	normi_eat_print(int id, long timestamp, t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->grim_mutex);
	if (philo->vars->grim_reaper != HERE)
	{
		pthread_mutex_unlock(&philo->vars->grim_mutex);

		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("%07li philo %d is eating\n", timestamp, id);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
	else
		pthread_mutex_unlock(&philo->vars->grim_mutex);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->grim_mutex);
	if (philo->vars->grim_reaper != HERE)
	{
		pthread_mutex_unlock(&philo->vars->grim_mutex);

		pthread_mutex_lock(&philo->nr_forks_mutex);
		if (philo->forks_in_hand == 2)
		{
			pthread_mutex_unlock(&philo->nr_forks_mutex);
			pthread_mutex_lock(&philo->eat_time_mutex);
			philo->start_eat_time = current_time(philo);
			pthread_mutex_unlock(&philo->eat_time_mutex);

			pthread_mutex_lock(&philo->vars->grim_mutex);
			if (philo->vars->grim_reaper != HERE)
			{
			pthread_mutex_unlock(&philo->vars->grim_mutex);
			normi_eat_print(philo->id, philo->start_eat_time, philo);
			}
			else 
				pthread_mutex_unlock(&philo->vars->grim_mutex);
			normi_ft_eat(philo);
			ft_usleep(philo->vars->time_to_eat, philo);
			ft_put_down_left_fork(philo);
			ft_put_down_right_fork(philo);
			ft_sleep(philo);
		}
		else
			pthread_mutex_unlock(&philo->nr_forks_mutex);
	}
	else
		pthread_mutex_unlock(&philo->vars->grim_mutex);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->grim_mutex);
	if (philo->vars->grim_reaper != HERE)
	{
		pthread_mutex_unlock(&philo->vars->grim_mutex);

		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("%07li philo %d is sleeping\n", current_time(philo), philo->id);
		pthread_mutex_unlock(&philo->vars->print_mutex);

		ft_usleep(philo->vars->time_to_sleep, philo);
		ft_think(philo);
	}
	else
		pthread_mutex_unlock(&philo->vars->grim_mutex);
}

void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->grim_mutex);
	if (philo->vars->grim_reaper != HERE)
	{
		pthread_mutex_unlock(&philo->vars->grim_mutex);
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("%07li philo %d is thinking\n", current_time(philo), philo->id);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
	else
		pthread_mutex_unlock(&philo->vars->grim_mutex);
}
