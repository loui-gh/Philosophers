//add -pthread link option otherwise this library won't work
#include "philo.h"
/*Your(s) program(s) should take the following arguments:
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] <-- last one optional*/

//each philo is a thread
//1 fork (int var) for each philo
int mails = 0;
void	*routine(void *data) 
{
	t_vars	*vars;

	vars = (t_vars *)data;//need to typecast
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(vars->table->mutex);
		/*check if this has been locked. If locked, other thread can't enter*/
		mails++;
		pthread_mutex_unlock(vars->table->mutex); /*everything between lock & unlock is performed in correct order*/
	}
	return (0);
}

int	main(int argc, char *argv[]) 
{
	if (ft_handle_input_errors(argc, argv) == 1)
		return (1);
	int		i;
	t_vars	*vars;
	t_table	table;

	vars = malloc(sizeof(t_vars));
	ft_init_vars(argc, argv, vars);
	i = 0;
	table.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * vars->number_of_philosophers);
	pthread_mutex_init(table.mutex, NULL);
	table.thread = (pthread_t *)malloc(sizeof(pthread_t) * vars->number_of_philosophers);
	while (i < vars->number_of_philosophers)
	{
		pthread_create(&table.thread[i], NULL, routine, &vars);
		printf("Philo %d created\n", i);
		i++;
	}

	while (i < vars->number_of_philosophers)
	{
		pthread_join(table.thread[i], NULL);
		printf("Thread %d fully formed\n", i);
		i++;
	}
		
	
	//free(vars);
	return (0);
}