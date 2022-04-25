/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:06:26 by Loui :)           #+#    #+#             */
/*   Updated: 2022/04/25 21:31:20 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> //add -pthread link option otherwise this library won't work
#include <sys/time.h>

typedef struct s_philo
{
	pthread_t		*thread; // each philo is its own thread
	// t_table	*table;
	int		id;
	int		status;
}	t_philo;
typedef struct s_table //what's at the table
{
	
	pthread_mutex_t	*mutex;
	t_philo		*philo; //!IDEA (Casper's idea)
	int			index;
	int			number_of_philosophers; //1
	int			time_to_die; //2
	int			time_to_eat; //3
	int			time_to_sleep; //4
	int			number_of_times_each_philosopher_must_eat; //5 - optional

	/* data */
}	t_table;



//utils
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
void	check_digits(char **argv);
int		ft_handle_input_errors(int argc, char *argv[]);
int		ft_init_table(int argc, char *argv[], t_table *table);

#endif