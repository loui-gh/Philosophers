/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:02:32 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/06 14:45:52 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_time(void)
{
    struct timeval  tp;
    long            start_time;

    gettimeofday(&tp, NULL);
    start_time = tp.tv_sec * 1000;
    start_time += tp.tv_usec / 1000;
    return (start_time);
}

long	current_time(t_philo *philo)
{
	long current_time = get_time() - philo->vars->start_time;
	return(current_time);
}
/*
printf("%07i Philosopher %d is sleeping.\n", \
        calculate_timedifference (philosopher), philosopher->id);
*/


int	grim_reaper(t_philo *philo)
{
	if ((current_time(philo) - philo->start_eat_time) > philo->vars->time_to_die)
		return (DEAD);
	else
		return (ALIVE);
}

/*if grim_reaper(philo[i] == DEATH)
	kill programme
*/