#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define ON_THE_TABLE 2

//number_of_philosophers time_to_die time_to_eat time_to_sleep
//[number_of_times_each_philosopher_must_eat]
typedef struct s_vars
{
		int					nr_philos;
		int					time_to_die;
		int					time_to_eat;
		int					time_to_sleep;
		int					meal_limit_per_philos;
		 pthread_mutex_t		eat_mutex;
		pthread_mutex_t		write_mutex;
		//pthread_mutex_t	*fork;
		
}		t_vars;

typedef struct s_philo 
{
	int				id;
	int				index;
	int				l_fork;//=2
	int				r_fork;//=2 at init
	int				nr_meals;
	struct s_philo	*l_philos;//+1
	struct s_philo	*r_philos;
	pthread_t		thread;
	t_vars			*vars;
}			t_philo;


//void	*ft_routine(void *arg)
/*create threads in a while-loop,
build baby routine ft, 
try to init mutexes in vars init ft.
split up into Makefile, philo.h, etc.
*/
/*DONE*/
/*init both structs (all philos + table)
*/

void	ft_init_philos(t_philo *philo, t_vars *vars, int nr_philos);
int		ft_atoi(const char *str);
void	ft_init_vars(t_vars *vars, char *argv[]);

int mails = 0;
pthread_mutex_t mutex;

void	*ft_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	//t_vars	vars;
	printf("Hello from thread %d\n", philo->id);
	for (int i = 0; i < 10000000; i++) {
		pthread_mutex_lock(&philo->vars->write_mutex);
		mails++;
		pthread_mutex_unlock(&philo->vars->write_mutex);
	}
	
	return (0);
}

int main(int argc, char* argv[])
{
	t_philo	*philo;
	t_vars	vars;
	int		nr_philos;
	int		i;

	argc++; //CHANGE LATER
	nr_philos = ft_atoi(argv[1]);
	
	//init structs
	philo = malloc(sizeof(t_philo) * nr_philos);
	//do I need to init all the mutexes here?
	ft_init_vars(&vars, argv);//here have successfully initialised 1 specific vars struct
	ft_init_philos(philo, &vars, nr_philos);

	pthread_mutex_init(&vars.write_mutex, NULL);
	i = 0;
	while (i < nr_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0) 
		{
			write(2, "Failed to create thread\n", 24);
			return 1;
		}
		i++;
	}

	i = 0;
	while (i < nr_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0) 
		{
			write(2, "Failed to create thread\n", 24);
			return 1;
		}
		i++;
	}
	printf("Number of mails: %d\n", mails);
	pthread_mutex_destroy(&vars.write_mutex);
	free(philo);
	return (0);

}

int	ft_atoi(const char *str)
{
	int	minus;
	int	res;
	int	i;

	res = 0;
	minus = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * minus);
}

void	ft_init_philos(t_philo *philo, t_vars *vars, int nr_philos)
{
	int		i;
	i = 0;
	while (i < nr_philos)
	{
		philo[i].id = i + 1;
		philo[i].vars = vars;//make sure all philos pointing to same vars struct
		philo[i].index = i;
		philo[i].l_philos = &philo[(i + nr_philos - 1) % nr_philos];
		philo[i].r_philos = &philo[(i + 1) % nr_philos];
		philo[i].l_fork = ON_THE_TABLE;
		philo[i].r_fork = ON_THE_TABLE;

		//printf("Hello from philosopher %d, index %d\n", philo[i].id, philo[i].index);
		i++;
	}
}

void	ft_init_vars(t_vars *vars, char *argv[])
{
	vars->nr_philos = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		vars->meal_limit_per_philos = ft_atoi(argv[5]);
	else
		vars->meal_limit_per_philos = -1;
	//INIT MUTEXES HERE
}
