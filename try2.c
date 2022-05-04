#include "philo.h"

void	*ft_routine(void *arg) 
{
	t_philo *philo;
	philo = (t_philo *)arg;
	
	//if (philo->l_fork == ON_THE_TABLE && philo->r_philos->l_fork == ON_THE_TABLE)
	if (philo->l_fork == ON_THE_TABLE && philo->r_philos->l_fork == ON_THE_TABLE)
	{
		pthread_mutex_lock(&philo->l_fork_mutex);
		philo->l_fork = TAKEN;
		pthread_mutex_unlock(&philo->l_fork_mutex);
		pthread_mutex_lock(&philo->r_fork_mutex);
		philo->r_philos->l_fork = TAKEN;
		pthread_mutex_unlock(&philo->r_fork_mutex);
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("philo %d has both forks\n", philo->id);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("Philo %d is waiting for fork\n", philo->id);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
	
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
	// pthread_mutex_init(&mutex, NULL);
	int i;
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
		pthread_mutex_destroy(&philo[j].r_fork_mutex);
		j++;
	}
	pthread_mutex_destroy(&vars.print_mutex);
//	pthread_mutex_destroy(vars.forks);
	free(philo);
	return (0);
}
