/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_shit_etc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeixner <konstantin.meixner@freenet.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:25:00 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/10 15:14:27 by kmeixner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	int doa;
	pthread_mutex_lock(&philo->doa_mutex);
	doa = philo->d_o_a;
	pthread_mutex_unlock(&philo->doa_mutex);

	if (doa == ALIVE)
	{
		pthread_mutex_lock(&philo->nr_forks_mutex);
		if (philo->forks_in_hand == 2)
		{
			pthread_mutex_unlock(&philo->nr_forks_mutex);
			
			pthread_mutex_lock(&philo->eat_time_mutex);
			philo->start_eat_time = current_time(philo);
			pthread_mutex_unlock(&philo->eat_time_mutex);
			
			philo_print(philo->id, philo->start_eat_time, 1, philo);
			
			pthread_mutex_lock(&philo->nr_meals_mutex);
			philo->nr_meals = philo->nr_meals + 1;
			pthread_mutex_unlock(&philo->nr_meals_mutex);
			if (philo->vars->meal_limit > 0)
				ft_check_meals(philo);
			
			ft_usleep(philo->vars->time_to_eat, philo);

			ft_put_down_left_fork(philo);
			ft_put_down_right_fork(philo);
			ft_sleep(philo);
		}
		else
			pthread_mutex_unlock(&philo->nr_forks_mutex);
	}
}

void	ft_sleep(t_philo *philo)
{
	int doa;
	pthread_mutex_lock(&philo->doa_mutex);
	doa = philo->d_o_a;
	pthread_mutex_unlock(&philo->doa_mutex);

	if (doa == ALIVE)
	{
		philo_print(philo->id, current_time(philo), 2, philo);
		ft_usleep(philo->vars->time_to_sleep, philo);
		ft_think(philo);
	}
}

void	ft_think(t_philo *philo)
{
	int doa;
	pthread_mutex_lock(&philo->doa_mutex);
	doa = philo->d_o_a;
	pthread_mutex_unlock(&philo->doa_mutex);
	if (doa == ALIVE)
		philo_print(philo->id, current_time(philo), 3, philo);
}
