#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define ON_THE_TABLE 2
#define TAKEN 1

//number_of_philosophers time_to_die time_to_eat time_to_sleep
//[number_of_times_each_philosopher_must_eat]
typedef struct s_vars
{
		int					nr_philos;
		int					time_to_die;
		int					time_to_eat;
		int					time_to_sleep;
		int					meal_limit;
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
/*

split up into Makefile, philo.h, etc.

*/

void	ft_init_philos(t_philo *philo, t_vars *vars, int nr_philos);
int		ft_atoi(const char *str);
void	ft_init_vars(t_vars *vars, char *argv[]);
void	ft_free(t_philo *philo);

int mails = 0;
pthread_mutex_t mutex;

void	*ft_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	/*TEST*/
	// printf("Hello from thread %d\n", philo->id);
	// for (int i = 0; i < 10000000; i++) {
	// 	pthread_mutex_lock(&philo->vars->write_mutex);
	// 	mails++;
	// 	pthread_mutex_unlock(&philo->vars->write_mutex);
	// }
	//INSTRUCTIONS: 
	/* 1) put forks */

	while (1) //if doens't work, you know it's sth to do with your mutexes
	{
		if (philo->l_fork == ON_THE_TABLE && philo->r_fork == ON_THE_TABLE)
		{
			pthread_mutex_lock(&philo->vars->write_mutex);//!!!!here you weren't actually locking the mutex because it was unitialised
			printf("Philosopher %d has taken a fork\n", philo->id);
			philo->l_fork = TAKEN;
			philo->r_fork = TAKEN;
			philo->r_philos->l_fork = TAKEN;
			philo->l_philos->r_fork = TAKEN;
			pthread_mutex_unlock(&philo->vars->write_mutex);
			pthread_mutex_lock(&philo->vars->eat_mutex);
			printf("Philosopher %d is eating\n", philo->id);
			usleep(philo->vars->time_to_eat * 1000); 
			philo->nr_meals--;
			if (philo->nr_meals == 0)
			{
				printf("GAME OVER\n");
				return (0);
			}
			//convert milli to micro
			philo->l_fork = ON_THE_TABLE;
			philo->r_fork = ON_THE_TABLE;
			philo->r_philos->l_fork = ON_THE_TABLE;
			philo->l_philos->r_fork = ON_THE_TABLE;
			pthread_mutex_unlock(&philo->vars->eat_mutex);
			pthread_mutex_lock(&philo->vars->write_mutex);//might have two threads trying to access same mem var at same time!!
			printf("Philosopher %d is sleeping\n", philo->id);
			usleep(philo->vars->time_to_sleep * 1000); //convert milli to micro
			pthread_mutex_unlock(&philo->vars->write_mutex);
		}
		else
		{
			pthread_mutex_lock(&philo->vars->write_mutex);
			printf("Philosopher %d is thinking\n", philo->id);
			if (philo->l_fork == ON_THE_TABLE && philo->r_fork == ON_THE_TABLE)
				pthread_mutex_unlock(&philo->vars->write_mutex);
		}
	}
	
	return (0);
}

int	ft_create_threads(t_philo *philo, int nr_philos)
{
	int i;
	i = 0;
	while (i < nr_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0) 
			return (1);
		i++;
	}

	i = 0;
	while (i < nr_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0) 
			return (1);
		i++;
	}
	return (0);
}

int main(int argc, char* argv[])
{
	t_philo	*philo;
	t_vars	vars;
	int		nr_philos;

	argc++; //CHANGE LATER
	nr_philos = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * nr_philos);
	//do I need to init all the mutexes here? -- nOPE
	ft_init_vars(&vars, argv);//here have successfully initialised 1 specific vars struct
	ft_init_philos(philo, &vars, nr_philos);
	if (ft_create_threads(philo, nr_philos) == 1)
	{
		write(2, "Failed to create thread\n", 24);
		return (1);
	}
	printf("Number of mails: %d\n", mails);
	ft_free(philo);
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

void ft_free(t_philo *philo)
{
	pthread_mutex_destroy(&philo->vars->write_mutex);
	pthread_mutex_destroy(&philo->vars->eat_mutex);
	free(philo);
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
		philo[i].nr_meals = vars->meal_limit;
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
		vars->meal_limit = ft_atoi(argv[5]);
	else
		vars->meal_limit = -1;
	
	pthread_mutex_init(&vars->write_mutex, NULL);
	pthread_mutex_init(&vars->eat_mutex, NULL);
	//INIT MUTEXES HERE
}
