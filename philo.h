/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:12:34 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/05 10:47:04 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

# define TAKEN 300
# define ON_THE_TABLE 100

typedef struct s_vars
{
		int					nr_philos;
		int					time_to_die;
		int					time_to_eat;
		int					time_to_sleep;
		int					meal_limit;
		int					*meals;
		pthread_mutex_t		mutex;
		pthread_mutex_t		print_mutex;
}		t_vars;

typedef struct s_philo 
{
	int				id;
	int				index;
	int				l_fork;
	int				forks_in_hand;
	int				nr_meals;
	struct s_philo	*l_philos;//+1
	struct s_philo	*r_philos;
	int				*ptr_r_fork;
	pthread_t		thread;
	pthread_mutex_t	l_fork_mutex;
	pthread_mutex_t	nr_forks_mutex;
	pthread_mutex_t	nr_meals_mutex;
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


//eat
void	ft_pick_up_left_fork(t_philo *philo);
void	ft_pick_up_right_fork(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_put_down_left_fork(t_philo *philo);
void	ft_put_down_right_fork(t_philo *philo);

#endif