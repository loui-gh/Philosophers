/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:06:26 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/27 22:54:17 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> //add -pthread link option otherwise this library won't work
#include <unistd.h> 
#include <sys/time.h>

typedef struct s_philo 
{
	int				id;
	pthread_t 		*thread; //make pthread a pointer, then it functions as a dynamic array in this instance
	pthread_mutex_t	*mutex;
}		t_philo;



//utils

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
void	ft_putstr(char *s);
void	ft_putchar(char c);
void	*ft_write(char *msg)

//error-handling
int		ft_isdigit(int c);
void	check_digits(char **argv);
int		ft_handle_input_errors(int argc, char *argv[]);

//philo_utils
//int		ft_init_table(int argc, char *argv[], t_table *table);

#endif