#include "philo.h"

void	ft_eat(t_philo *philo)
{
		pthread_mutex_lock(&philo->nr_forks_mutex);
		if (philo->forks_in_hand == 2)
		{
			pthread_mutex_lock(&philo->vars->print_mutex);
			printf("philo %d is eating\n", philo->id);
			usleep(philo->vars->time_to_eat * 1000);
			pthread_mutex_unlock(&philo->vars->print_mutex);
			ft_put_down_left_fork(philo);
			ft_put_down_right_fork(philo);
		}
		else
			pthread_mutex_unlock(&philo->nr_forks_mutex);
		
		
}



// void	ft_think(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->vars->print_mutex);
// 	printf("philo %d is thinking\n", philo->id);
// 	pthread_mutex_unlock(&philo->vars->print_mutex);
// }


void	*ft_routine(void *arg) 
{
	t_philo *philo;
	philo = (t_philo *)arg;
	ft_pick_up_left_fork(philo);
	ft_pick_up_right_fork(philo);
	ft_eat(philo);
	return(0);
}


int main(int argc, char* argv[])
{
	t_philo	*philo;
	t_vars	vars;
	int		nr_philos;

	if (ft_handle_input_errors(argc, argv) == 1)
		return (1);
	nr_philos = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * nr_philos);
	//init vars
	ft_init_vars(&vars, argv);//here have successfully initialised 1 specific vars struct
	ft_init_philos(philo, &vars, nr_philos);
	int i;
	i = 0;
	while (i < nr_philos)
	{
		//don't init ptr to mutex, just give it addy
		philo[i].ptr_mutex = &philo[i].r_philos->l_fork_mutex;
		i++;
	}
	i = 0;
	while (i < vars.nr_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0) 
		{
			perror("Failed to create thread");
			return 1;
		}
		i++;
	}
	
	i = 0;
	while (i < vars.nr_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0) 
		{
			//write(2, "5\n", 2);
			return 1;
		}
		i++;
	}
	int j = 0;
	while (j < nr_philos)
	{
		pthread_mutex_destroy(&philo[j].l_fork_mutex);
		pthread_mutex_destroy(&philo[j].nr_forks_mutex);
		pthread_mutex_destroy(&philo[j].nr_meals_mutex);
		j++;
	}
	pthread_mutex_destroy(&vars.print_mutex);
	pthread_mutex_destroy(&vars.mutex);

	free(philo);
	return (0);
}
