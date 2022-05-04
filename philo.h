/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:12:34 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/04 19:37:41 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

# define TAKEN 100
# define ON_THE_TABLE 201

typedef struct s_vars
{
		int					nr_philos;
		int					time_to_die;
		int					time_to_eat;
		int					time_to_sleep;
		int					meal_limit;
		
		pthread_mutex_t		print_mutex;
		pthread_mutex_t		read_mutex;
}		t_vars;

typedef struct s_philo 
{
	int				id;
	int				index;
	int				l_fork;//=2
	//int				r_fork;//=2 at init
	int				nr_meals;
	struct s_philo	*l_philos;//+1
	struct s_philo	*r_philos;
	int				*ptr_r_fork;
	pthread_t		thread;
	pthread_mutex_t	l_fork_mutex;
	pthread_mutex_t	*ptr_mutex;
	t_vars			*vars;
}			t_philo;

//utils
size_t	ft_strlen(const char *str);
int	ft_atoi(const char *str);
void	ft_putnbr(int c);

//input errors
int	ft_handle_input_errors(int argc, char *argv[]);

//init structs
void	ft_init_vars(t_vars *vars, char *argv[]);
void	ft_init_philos(t_philo *philo, t_vars *vars, int nr_philos);

#endif