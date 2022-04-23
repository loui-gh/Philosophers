#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> //add -pthread link option otherwise this library won't work

int				mails = 0;
pthread_mutex_t	mutex;
void	*routine() 
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		/*check if this has been locked. If locked, other thread can't enter*/
		mails++;
		pthread_mutex_unlock(&mutex); /*everything between lock & unlock is performed in correct order*/
	}
	
}

int	main(int argc, char *argv[]) 
{
    pthread_t thr[4]; //can put this in an array
	/*api stores info about thread in var of type pthread_t. 
	One for each thread can put that variable inside a struct */
	pthread_mutex_init(&mutex, NULL);
		//arg0 = address of mutex var
	int i;
	//if you call pthread_create and _join in the same loop,
	//the threads will execute consecutavly -- not the goal!!
	for (i=0; i < 4; i++)
	{
		if (pthread_create(&thr[i], NULL, &routine, NULL) != 0) 
		{
			perror("Failed to create thread\n");
			return (1);
		}
		printf("Thread %d has started\n", i);
	}//&thr[i] SAME AS thr + i

	 //might not have enough resources for thread, so need to error-check
	//arg0 ptr to t1 var, hence &
	//arg1 customisation. Passing NULL will use defaults. Andrei used defaults
	//arg2 passes ft as argument, which is why you ref with &
	//arg3 arg passed into "routine" Andrei passed a struct
	for (i=0; i < 4; i++)
	{
		if (pthread_join(thr[i], NULL) != 0) {
			return (2);
		}
		printf("Thread %d has finished execution\n", i);
	}


		/*very important!! We need to wait for pthread to finish execution. 
		We can't have process finish and thread be unfinished. pthread_join makes it wait*/

	
		//arg0 struct, which holds info for thread
		//arg1 ptr that gets result from that thread. routine is void*, so ==NULL here
	pthread_mutex_destroy(&mutex);//every mutex_init requires a destroy
	printf("Number of mails: %d\n", mails);
	return (0);
}