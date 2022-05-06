/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_up_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:51:09 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/06 11:27:45 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_pick_up_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork_mutex);
	if (philo->l_fork == ON_THE_TABLE)
	{
		philo->l_fork = TAKEN;
		philo->forks_in_hand++;
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("%07li %d has taken LEFT fork, forks in hand = %d\n", current_time(philo), philo->id, philo->forks_in_hand);
		pthread_mutex_unlock(&philo->vars->print_mutex);
		
		pthread_mutex_unlock(&philo->l_fork_mutex);//
		
	}
	else 
		pthread_mutex_unlock(&philo->l_fork_mutex);
	
}

void	ft_pick_up_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->ptr_mutex);
	if (philo->r_philos->l_fork == ON_THE_TABLE)
	{
		philo->r_philos->l_fork = TAKEN;
		philo->forks_in_hand++;
		pthread_mutex_unlock(philo->ptr_mutex);
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("%07li %d has taken RIGHT fork, forks in hand = %d\n", current_time(philo), philo->id, philo->forks_in_hand);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
	else
		pthread_mutex_unlock(philo->ptr_mutex);
}

void	ft_put_down_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork_mutex);
	if (philo->l_fork == TAKEN)
	{
		philo->l_fork = ON_THE_TABLE;
		philo->forks_in_hand--;
		pthread_mutex_unlock(&philo->nr_forks_mutex);
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("philo %d has PUT DOWN her left fork, forks in hand = %d\n", philo->id, philo->forks_in_hand);
		pthread_mutex_unlock(&philo->vars->print_mutex);
		pthread_mutex_unlock(&philo->l_fork_mutex);

	}
	else
		pthread_mutex_unlock(&philo->l_fork_mutex);
}

void	ft_put_down_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->ptr_mutex);
	if (philo->r_philos->l_fork == TAKEN)
	{
		philo->r_philos->l_fork = ON_THE_TABLE;
		philo->forks_in_hand--;
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("philo %d has PUT DOWN her right fork, forks in hand = %d\n", philo->id, philo->forks_in_hand);
		pthread_mutex_unlock(&philo->vars->print_mutex);
		pthread_mutex_unlock(philo->ptr_mutex);//right fork placed down
		ft_sleep(philo);//SLEEP FT STARTS
	}
	else
		pthread_mutex_unlock(philo->ptr_mutex);
}