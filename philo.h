/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:12:34 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/12 14:41:17 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKEN 300
# define ON_THE_TABLE 100
# define HERE 0

typedef struct s_vars
{
	int					nr_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meal_limit;
	long				start_time;
	int					grim_reaper;
	pthread_mutex_t		grim_mutex;
	pthread_mutex_t		print_mutex;
}		t_vars;

typedef struct s_philo
{
	int				id;
	int				l_fork;
	int				nr_meals;
	long			start_eat_time;
	struct s_philo	*l_philos;
	struct s_philo	*r_philos;
	pthread_t		thread;
	pthread_mutex_t	l_fork_mutex;
	pthread_mutex_t	*ptr_mutex;
	int				forks_in_hand;
	pthread_mutex_t	nr_forks_mutex;
	pthread_mutex_t	eat_time_mutex;
	pthread_mutex_t	nr_meals_mutex;
	t_vars			*vars;
}			t_philo;

//utils
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
void	ft_putnbr(int c);
void	ft_write(char *msg);
void	philo_print(int id, long timestamp, int msg_categorie, t_philo *philo);
//temp utils
int		ft_write_id_status(int id, int status);

//input errors
int		ft_handle_input_errors(int argc, char *argv[]);

//init structs n' threads
void	ft_init_vars(t_vars *vars, char *argv[]);
void	ft_init_r_fork_mutex(t_philo *philo);
void	ft_init_philos(t_philo *philo, t_vars *vars, int nr_philos);
int		ft_create_threads(t_philo *philo);
void	*ft_routine(void *arg);

//free structs + threads
void	ft_free(t_philo *philo, int nr_philos);

//eat
void	ft_pick_up_left_fork(t_philo *philo);
void	ft_pick_up_right_fork(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_put_down_left_fork(t_philo *philo);
void	ft_put_down_right_fork(t_philo *philo);

//think
void	ft_think(t_philo *philo);
//sleep
void	ft_sleep(t_philo *philo);

//time
long	get_time(void);
void	ft_wait(int nr_microseconds);
long	current_time(t_philo *philo);
void	ft_usleep(int duration, t_philo *philo);
//DEATH
int		ft_survival_check(t_philo *philo);
void	one_guy(t_philo *philo); // <-- for if one philo only
void	ft_check_meals(t_philo *philo);

#endif