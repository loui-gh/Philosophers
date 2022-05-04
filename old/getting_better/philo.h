/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:12:34 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/02 08:47:05 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define TAKEN 0
# define ON_THE_TABLE 2

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> //add -pthread link option otherwise this library won't work
#include <unistd.h> 
#include <sys/time.h>

typedef struct s_vars
{
		int					nr_philos;
		long unsigned int	time_to_eat;//given in milliseconds*//
		long unsigned int	time_to_sleep;//given in milliseconds*//
		int					meal_limit;
		pthread_mutex_t		eat_mutex;
		pthread_mutex_t		sleep_mutex;
		pthread_mutex_t		write;
		//pthread_mutex_t	*fork;
		
}		t_vars;

typedef struct s_philo 
{
	int			id;
	int			index;
	int			l_fork;//=2
	int			r_fork;//=2 at init
	int			nr_meals;
	struct s_philo	*l_philos;//+1
	struct s_philo	*r_philos;
	pthread_t 		thread;
	t_vars		*vars;
}		t_philo;


//philos & threading
void	ft_init_philos(t_philo *philo, t_vars *vars, int nr_philos);
void	*ft_routine(void *arg);


//error handling
int		ft_handle_input_errors(int argc, char *argv[]);
void	check_digits(char **argv);
int		ft_isdigit(int c);

//utils
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);

//print fts
//void	hello(int n, t_philo *philo); //can I point to specific philos within the routine ft? -- doesn't look like it

void	ft_putnbr(long n);
void	ft_write(char *msg);

#endif