/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:02:32 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/10 22:10:38 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Returns the timestamp in milliseconds
*/
long	get_time(void)
{
	struct timeval	tp;
	long			start_time;

	gettimeofday(&tp, NULL);
	start_time = tp.tv_sec * 1000;
	start_time += tp.tv_usec / 1000;
	return (start_time);
}

long	current_time(t_philo *philo)
{
	long	current_time;

	current_time = get_time() - philo->vars->start_time;
	return (current_time);
}

void	ft_wait(int nr_microseconds)
{
	long	start_value;

	start_value = get_time();
	while (get_time() < nr_microseconds + start_value)
		;
}

void	ft_usleep(int duration, t_philo *philo)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < duration)
	{
		usleep(50);
		if (ft_survival_check(philo) == 1)
			break ;
	}
}
