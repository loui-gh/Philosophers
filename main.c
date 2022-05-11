/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:10:26 by Loui :)           #+#    #+#             */
/*   Updated: 2022/05/10 22:17:32 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* ./philo
	arg[1] number_of_philosophers
	arg[2] time_to_die
	arg[3] time_to_eat
	arg[4] time_to_sleep
	? argv[5] number_of_times_each_philosopher_must_eat
*/

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		doa;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->doa_mutex);
	doa = philo->d_o_a;
	pthread_mutex_unlock(&philo->doa_mutex);
	while (1 && doa == ALIVE)
	{
		if (ft_survival_check(philo) == 1)
			break ;
		ft_pick_up_left_fork(philo);
		ft_pick_up_right_fork(philo);
		ft_eat(philo);
	}
	return (0);
}

void	one_guy(t_philo *philo)
{
	ft_pick_up_left_fork(philo);
	ft_wait(philo->vars->time_to_die);
	philo->d_o_a = DEAD;
	printf("%07li philo 1 died\n", current_time(philo));
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	t_vars	vars;

	if (ft_handle_input_errors(argc, argv) == 1)
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	ft_init_vars(&vars, argv);
	ft_init_philos(philo, &vars, ft_atoi(argv[1]));
	if (vars.nr_philos == 1)
		one_guy(philo);
	ft_create_threads(philo);
	ft_free(philo, vars.nr_philos);
	return (0);
}
