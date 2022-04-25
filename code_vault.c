#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> //add -pthread link option otherwise this library won't work
#include <sys/time.h>


// 	 //might not have enough resources for thread, so need to error-check
typedef struct s_data
{
	
	pthread_t 		t1;	//place where api can store info about the thread
	pthread_t 		t2;
}	t_data;

pthread_mutex_t	mutex;




int mails = 0;

void	*ft()
{

	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}
int main(int argc, char *argv[])
{
	t_data	data;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&data.t1, NULL, (void *) &ft, NULL);

	//arg0 ptr to t1 var, hence &
	//arg1 customisation. Passing NULL will use defaults. Andrei used defaults
	//arg2 passes ft as argument, which is why you ref with &
	//arg3 arg passed into "routine" Andrei passed a struct

	/*need thread to finish execution first. Use ft below to check if thread is done*/
	pthread_join(data.t1, NULL);
	//arg0 is thread to join
	//arg1 is pointer to return value of thread, NULL if not needed
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return 0;
}

void	ft_putnbr_fd(long n)
{
	int		remainder;
	char	digit;

	if (n < 0)
	{
		write(1, "-", 1);
		n = n * -1;
	}
	if (n > 9)
	{
		remainder = n % 10;
		ft_putnbr_fd(n / 10);
		digit = remainder + '0';
		write(1, &digit, 1);
	}
	else
	{
		digit = n + '0';
		write(1, &digit, 1);
	}
}
