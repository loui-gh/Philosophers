/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:48:03 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/11 00:04:58 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	minus;
	int	res;
	int	i;

	res = 0;
	minus = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * minus);
}

/* 
EAT 1
SLEEP 2
THINK 3
DEATH 4
*/
void	philo_print(int id, long timestamp, int msg_categorie, t_philo *philo)
{
	int	death;

	pthread_mutex_lock(&philo->vars->grim_reaper_mutex);
	death = philo->vars->grim_reaper;
	pthread_mutex_unlock(&philo->vars->grim_reaper_mutex);
	if (msg_categorie == 1 && death != HERE)
	{
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("%07li philo %d is eating\n", timestamp, id);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
	if (msg_categorie == 2 && death != HERE)
	{
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("%07li philo %d is sleeping\n", timestamp, id);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
	if (msg_categorie == 3 && death != HERE)
	{
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("%07li philo %d is thinking\n", timestamp, id);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
}

void	ft_write(char *msg)
{
	int	i;

	i = 0;
	while (msg[i] != '\0')
	{
		write(1, &msg[i], 1);
		i++;
	}
	return ;
}

void	ft_free(t_philo *philo, int nr_philos)
{
	int	j;

	j = 0;
	while (j < nr_philos)
	{
		pthread_mutex_destroy(&philo[j].l_fork_mutex);
		pthread_mutex_destroy(&philo[j].nr_forks_mutex);
		pthread_mutex_destroy(&philo[j].nr_meals_mutex);
		pthread_mutex_destroy(&philo[j].eat_time_mutex);
		pthread_mutex_destroy(&philo[j].doa_mutex);
		j++;
	}
	pthread_mutex_destroy(&philo->vars->print_mutex);
	pthread_mutex_destroy(&philo->vars->grim_reaper_mutex);
	free(philo);
}
