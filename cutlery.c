/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutlery.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:51:09 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/10 23:53:54 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_pick_up_left_fork(t_philo *philo)
{
	int	doa;

	pthread_mutex_lock(&philo->doa_mutex);
	doa = philo->d_o_a;
	pthread_mutex_unlock(&philo->doa_mutex);
	if (philo->id % 2 != 0)
		usleep(5000);
	if (doa == ALIVE)
	{
		pthread_mutex_lock(&philo->l_fork_mutex);
		if (philo->l_fork == ON_THE_TABLE)
		{
			philo->l_fork = TAKEN;
			pthread_mutex_unlock(&philo->l_fork_mutex);
			pthread_mutex_lock(&philo->nr_forks_mutex);
			philo->forks_in_hand++;
			pthread_mutex_unlock(&philo->nr_forks_mutex);
			pthread_mutex_lock(&philo->vars->print_mutex);
			printf("%07li %d has taken LEFT fork\n", \
				current_time(philo), philo->id);
			pthread_mutex_unlock(&philo->vars->print_mutex);
		}
		else
			pthread_mutex_unlock(&philo->l_fork_mutex);
	}
}

void	ft_pick_up_right_fork(t_philo *philo)
{
	int	doa;

	pthread_mutex_lock(&philo->doa_mutex);
	doa = philo->d_o_a;
	pthread_mutex_unlock(&philo->doa_mutex);
	if (doa == ALIVE)
	{
		pthread_mutex_lock(philo->ptr_mutex);
		if (philo->r_philos->l_fork == ON_THE_TABLE)
		{
			philo->r_philos->l_fork = TAKEN;
			pthread_mutex_unlock(philo->ptr_mutex);
			pthread_mutex_lock(&philo->nr_forks_mutex);
			philo->forks_in_hand++;
			pthread_mutex_unlock(&philo->nr_forks_mutex);
			pthread_mutex_lock(&philo->vars->print_mutex);
			printf("%07li %d has taken RIGHT fork\n", \
				current_time(philo), philo->id);
			pthread_mutex_unlock(&philo->vars->print_mutex);
		}
		else
			pthread_mutex_unlock(philo->ptr_mutex);
	}
}

void	ft_put_down_left_fork(t_philo *philo)
{
	int	doa;

	pthread_mutex_lock(&philo->doa_mutex);
	doa = philo->d_o_a;
	pthread_mutex_unlock(&philo->doa_mutex);
	if (doa == ALIVE)
	{
		pthread_mutex_lock(&philo->l_fork_mutex);
		if (philo->l_fork == TAKEN)
		{
			philo->l_fork = ON_THE_TABLE;
			pthread_mutex_unlock(&philo->l_fork_mutex);
			pthread_mutex_lock(&philo->nr_forks_mutex);
			philo->forks_in_hand--;
			pthread_mutex_unlock(&philo->nr_forks_mutex);
		}
		else
			pthread_mutex_unlock(&philo->l_fork_mutex);
	}
}

void	ft_put_down_right_fork(t_philo *philo)
{
	int	doa;

	pthread_mutex_lock(&philo->doa_mutex);
	doa = philo->d_o_a;
	pthread_mutex_unlock(&philo->doa_mutex);
	if (doa == ALIVE)
	{
		pthread_mutex_lock(philo->ptr_mutex);
		if (philo->r_philos->l_fork == TAKEN)
		{
			philo->r_philos->l_fork = ON_THE_TABLE;
			pthread_mutex_unlock(philo->ptr_mutex);
			pthread_mutex_lock(&philo->nr_forks_mutex);
			philo->forks_in_hand--;
			pthread_mutex_unlock(&philo->nr_forks_mutex);
		}
		else
			pthread_mutex_unlock(philo->ptr_mutex);
	}
}
