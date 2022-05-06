#include "philo.h"

void	*ft_routine(void *arg) 
{
	t_philo *philo;
	philo = (t_philo *)arg;
	ft_pick_up_left_fork(philo);
	ft_pick_up_right_fork(philo);
	ft_eat(philo);
	return(0);
}

void	*coffin(void)
{
	t_philo *philo;
	int i = 0;

	while (i < philo->vars->nr_philos)
	{
		i++;
	}
	printf("COFFIN FUNCTION\n");
	return (0);
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
	//might need dbl-ptr to put this in separate ft
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
	
	//the ft_routine here should just check status of threads in an endless while loop
	// that resets i to zero once i = nr philos
	pthread_t			the_grim_reaper;
	//pass t_philo ptr_philo as arg to 
	if (pthread_create(&the_grim_reaper, NULL, &coffin, NULL) != 0) 
		{
			perror("Failed to create thread");
			return 1;
		}
	if (pthread_join(philo[i].thread, NULL) != 0) 
		{
			//write(2, "5\n", 2);
			return 1;
		}
	ft_free(philo, nr_philos);
	return (0);
}