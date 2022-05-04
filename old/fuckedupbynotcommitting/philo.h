/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:22:44 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/28 23:01:46 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> //add -pthread link option otherwise this library won't work
#include <unistd.h> 
#include <sys/time.h>

typedef struct s_vars
{
		pthread_mutex_t	mutex;
		unsigned long	start_time;
		int				nr_philos;
}		t_vars;

typedef struct s_philo 
{
	int				id;
	pthread_t 		thread; //make pthread a pointer, then it functions as a dynamic array in this instance
	//t_vars		*vars;
	//pthread_mutex_t	*mutex;
}		t_philo;
//pthread_mutex_t	mutex;//need to lock correct mutex!

//utils
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
void	ft_putnbr(long n);
void	ft_putstr(char *s);

//input error-handling
int		ft_handle_input_errors(int argc, char *argv[]);
void	check_digits(char **argv);
int		ft_isdigit(int c);


//structs 'n stuff
void	ft_init_philos(t_philo *philo, int i);
void	init_vars(t_vars *vars, char *argv[]);

//philosophising
void	ft_write(char *msg);
//unsigned long	get_time(t_vars *vars);
void	*ft_routine(void *arg);

#endif