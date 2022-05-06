/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_shit_etc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:25:00 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/06 11:27:03 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
		pthread_mutex_lock(&philo->nr_forks_mutex);
		if (philo->forks_in_hand == 2)
		{
			
			pthread_mutex_lock(&philo->vars->print_mutex);
			printf("%07li philophilo %d is eating\n", current_time(philo), philo->id);
			pthread_mutex_unlock(&philo->vars->print_mutex);
			usleep(philo->vars->time_to_eat * 1000);
			//check_meals
			ft_put_down_left_fork(philo);
			ft_put_down_right_fork(philo);//ft_sleep goes here
		}
		else
			pthread_mutex_unlock(&philo->nr_forks_mutex);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("%07li philophilo %d is sleeping\n", current_time(philo), philo->id);
	pthread_mutex_unlock(&philo->vars->print_mutex);
	usleep(philo->vars->time_to_sleep * 1000);
}
void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("philo %d is thinking\n", philo->id);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}
