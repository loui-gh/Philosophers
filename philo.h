/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:12:34 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/29 14:39:36 by Loui :)          ###   ########.fr       */
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
		pthread_mutex_t	write;
}		t_vars;

typedef struct s_philo 
{
	int			id;
	pthread_t 	thread; //make pthread a pointer, then it functions as a dynamic array in this instance
	t_vars		*vars;
	//pthread_mutex_t	*mutex;
}		t_philo;
//pthread_mutex_t	mutex;//need to lock correct mutex!

//philos & threading
void	ft_init_philos(t_philo *philo, int i);
void	*ft_routine(void *arg);


//error handling
int		ft_handle_input_errors(int argc, char *argv[]);
void	check_digits(char **argv);
int		ft_isdigit(int c);

//utils
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);

//print fts
void	hello(int n);
void	ft_putnbr(long n);
void	ft_write(char *msg);

#endif