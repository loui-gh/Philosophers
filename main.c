#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> //add -pthread link option otherwise this library won't work
#include <unistd.h> 
#include <sys/time.h>

typedef struct s_vars
{
		pthread_mutex_t	mutex;
}		t_vars;

typedef struct s_philo 
{
	int				id;
	pthread_t 		thread; //make pthread a pointer, then it functions as a dynamic array in this instance
	//pthread_mutex_t	*mutex;
}		t_philo;
//pthread_mutex_t	mutex;//need to lock correct mutex!


int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
void	ft_init_philos(t_philo *philo, int i);
void	*ft_routine(void *arg);
int		ft_handle_input_errors(int argc, char *argv[]);
void	check_digits(char **argv);
int		ft_isdigit(int c);
void	ft_putnbr(long n);
void	ft_write(char *msg)
{
	write(1, msg, ft_strlen(msg));
}
void	*ft_routine(void *arg)
{
	t_philo *philo;
	t_vars	vars;
	philo = (t_philo *)arg;
	///philo->mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_lock(&vars.mutex);
	ft_write("Hello from thread id ");
	ft_putnbr(philo->id);
	ft_write("\n");
	//printf("Hello from thread \n");
	ft_write("Ending thread\n");
	pthread_mutex_unlock(&vars.mutex);
}

int	main(int argc, char *argv[])
{
	int		nr_philos;
	int		i;
	t_philo	*philo;
	t_vars	vars;

	
	
	if (ft_handle_input_errors(argc, argv) != 0)
		return (0);
	nr_philos = ft_atoi(argv[1]);
	
	philo = malloc(sizeof(t_philo) * nr_philos);

	

	pthread_mutex_init(&vars.mutex, NULL);

	//philo->mutex = malloc(sizeof(pthread_mutex_t) * nr_philos);//it is essential to malloc mutexes. It is a big fucking variable??
	//init philos as an array of structures
	i = 0;
	while (i < nr_philos)
	{
		
		ft_init_philos(philo, i);
		//need a mutex_init for every philo?
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0) 
		{
			perror("Failed to create thread");
			return 1;
		}
		i++;
	}
	
	i = 0;
	while (i < nr_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0) 
		{
			write(2, "5\n", 2);
			return 3;
		}
		i++;
	}
	pthread_mutex_destroy(&vars.mutex);
	return (0);
}
static void	normi_check_digits(int j)
{
	j++;
	printf("Error: list may only contain digits\n");
	exit (EXIT_FAILURE);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

void	check_digits(char **argv)
{
	char	*c;
	int		i;
	int		j;

	i = 1;
	while (argv[i])
	{
		c = argv[i];
		j = 0;
		if (ft_strlen(c) == 0)
			normi_check_digits(j);
		if (ft_strlen(c) > 1 && c[0] == '-')
		{
			printf("Error: list may only contain +ve numbers\n");
			exit (EXIT_FAILURE);
		}
		while (c[j] != '\0')
		{
			if (ft_isdigit(c[j]) == 0)
				normi_check_digits(j);
			j++;
		}
		i++;
	}
}

int	ft_handle_input_errors(int argc, char *argv[])
{
	check_digits(argv);
	if (argc != 5 && argc != 6)
	{
		printf("Error: too few or too many args entered\n");
		return (1);
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_init_philos(t_philo *philo, int i)
{
	//ptr[i]->thread = malloc(sizeof(pthread_t));
	philo[i].id = i + 1;
	//Philosopher status: 0 - thinking, 1 - eating, 2 - sleeping -- create a mutex lock for that
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

void	ft_putnbr(long n)
{
	int		remainder;
	char	digit;
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		digit = n + '0';
		write(1, &digit, 1);
	}
}
