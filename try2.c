#include "philo.h"
// static void	ft_take_r_fork(t_philo *philo)
// {
// 	if (philo->id %2 != 0 )
// 		usleep(2);


// 	pthread_mutex_lock(&philo->r_fork_mutex);
// 	if (philo->r_philos->l_fork == ON_THE_TABLE)
// 	{
// 		philo->r_philos->l_fork = TAKEN;
// 		pthread_mutex_unlock(&philo->r_fork_mutex);
// 		pthread_mutex_lock(&philo->vars->print_mutex);
// 		printf("philo %d has taken RIGHT fork\n", philo->id);
// 		pthread_mutex_unlock(&philo->vars->print_mutex);
// 		usleep(2);	
// 	}
// 	else 
// 	{
// 		pthread_mutex_lock(&philo->vars->print_mutex);
// 		printf("philo %d is waiting\n", philo->id);
// 		pthread_mutex_unlock(&philo->vars->print_mutex);
// 		pthread_mutex_unlock(&philo->r_fork_mutex);
// 	}
// }

//unfisnihed changes

// static void	ft_take_l_fork(t_philo *philo)
// {
	
// 	if (philo->id %2 == 0 )
// 		usleep(20);

// 	pthread_mutex_lock(&philo->l_fork_mutex);
// 	pthread_mutex_lock(&philo->r_fork_mutex);
// 	if (philo->l_fork == ON_THE_TABLE && philo->r_philos->l_fork == ON_THE_TABLE)
// 	{
// 		philo->l_fork = TAKEN;
// 		pthread_mutex_unlock(&philo->l_fork_mutex);
// 		philo->r_philos->l_fork = TAKEN;
// 		pthread_mutex_unlock(&philo->r_fork_mutex);
// 		pthread_mutex_lock(&philo->vars->print_mutex);
// 		printf("philo %d has taken left fork\n", philo->id);
// 		pthread_mutex_unlock(&philo->vars->print_mutex);
// 		usleep(2);	
// 	}
// 	else 
// 	{
// 		pthread_mutex_unlock(&philo->l_fork_mutex);
// 		pthread_mutex_lock(&philo->vars->print_mutex);
// 		printf("philo %d is waiting\n", philo->id);
// 		pthread_mutex_unlock(&philo->vars->print_mutex);
// 	}
// }
// void	*ft_routine(void *arg) 
// {
// 	t_philo *philo;
// 	philo = (t_philo *)arg;
	
// 	//pthread_mutex_lock(&philo->vars->read_mutex); //one of these, so won't lock indv variables
	
// 	ft_take_r_fork(philo);
// 	ft_take_l_fork(philo);
	
// 	return(0);
// }

void	*ft_routine(void *arg) 
{
	t_philo *philo;
	philo = (t_philo *)arg;
	//if start time is zero

	if (philo->id %2 == 0 )
	{
 		//usleep(sleep time - 2 microseconds);//watch how long they sleep!
	//pthread_mutex_lock(&philo->vars->read_mutex); //one of these, so won't lock indv variables
	pthread_mutex_lock(&philo->l_fork_mutex);
	if (philo->l_fork == ON_THE_TABLE)
	{
		philo->l_fork = TAKEN;
		pthread_mutex_unlock(&philo->l_fork_mutex);
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("philo %d has taken left fork\n", philo->id);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
	else 
		pthread_mutex_unlock(&philo->l_fork_mutex);
	pthread_mutex_lock(philo->ptr_mutex);
	if (philo->r_philos->l_fork == ON_THE_TABLE)
	{
		philo->r_philos->l_fork = TAKEN;
		pthread_mutex_unlock(philo->ptr_mutex);
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("philo %d has taken RIGHT fork\n", philo->id);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}
	else
		pthread_mutex_unlock(philo->ptr_mutex);
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
		j++;
	}
	pthread_mutex_destroy(&vars.print_mutex);
	pthread_mutex_destroy(&vars.read_mutex);

	free(philo);
	return (0);
}
