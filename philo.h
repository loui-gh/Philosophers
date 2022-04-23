/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:06:26 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/23 18:33:34 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> //add -pthread link option otherwise this library won't work

typedef struct s_table
{
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
	int				forks_on_table;
	// int				*is_taken;
	// pthread_mutex_t	general;
	// long			*start_time;
	// long			*init_time;
	// int				*eat;
	// int				*status;
	// int				is_dead;
	// int				nb_philo;
	// int				*waiting_list;
	// int				position;
}				t_table;

typedef struct s_vars
{
	pthread_t	*thread;
	t_table		*table;
	int			number_of_philosophers; //1
	int			time_to_die; //2
	int			time_to_eat; //3
	int			time_to_sleep; //4
	int			number_of_times_each_philosopher_must_eat; //5 - optional
	/* data */
}	t_vars;

//utils
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
void	check_digits(char **argv);
int		ft_handle_input_errors(int argc, char *argv[]);
int		ft_init_vars(int argc, char *argv[], t_vars *vars);

#endif