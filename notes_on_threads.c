#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>//add -pthread link option otherwise this library won't work
#include <unistd.h> 
#include <time.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
//HERE: Create 10 threads, each taking a UNIQUE prime from the primes array above
//TRANSLATION TO PHILOSOPHERS: Take each philo and assign her status randomly

void *routine(void *arg)//every single void ptr has the same size
{
	sleep(1);
	int index = *(int *)arg; //cast arg to int ptr, then dereference it
	printf("%d ", primes[index]);
	free(arg);
}

int main(int argc, char *argv[])
{
	pthread_t th[10];
	int i;
	int *a;

	i = 0;
	while (i < 10)
	{
		a = malloc(sizeof(int));
		*a = i; //by giving it an index, you get one of each value in the array
		if (pthread_create(&th[i], NULL, &routine, a) != 0) //arg3 needs to be ref of i
			printf("Failed to create thread\n");
		i++;
		//can't free here, cos maybe thread hasn't finished execution
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			printf("Failed to join thread\n");
		i++;
	}
	return (0);
}
//RETURNING A VALUE FROM A THREAD --VERY INTERESTING PART ON PTRS TO THREAD VALUES

// void* roll_dice() {
//     int value = (rand() % 6) + 1; // % is modulo, so it will return a random number between 1 and 6
//     int* result = malloc(sizeof(int));
//     *result = value;
//     // printf("%d\n", value);
//     printf("Thread result: %p\n", result);
//     return (void*) result; // need to return a pointer to this LOCAL result.
// } // Can't return ref to value local to this ft [return (void*) &value;] 
// //because the stack value is destroyed after the ft returns. This is why need to DYNAMICALLY ALLOCATE
// // on line 10

// int main(int argc, char* argv[]) {
//     int* res;
//     srand(time(NULL));
//     pthread_t th;
//     if (pthread_create(&th, NULL, &roll_dice, NULL) != 0) {
//         return 1;
//     }
//     if (pthread_join(th, (void**) &res) != 0) {
//         return 2; //2nd argument is a pointer to a pointer, so we need to dereference it
//     }
//     printf("Main res: %p\n", res); //ptrs have same addy cos res pts to result of roll_dice(), 
//     printf("Result: %d\n", *res); //as does result.
//     free(res);
//     return 0;
// }

//THREADS CAN BE CREATED FROM OTHER THREADS...
//THREADS IN A LOOP

// int mails = 0;
// pthread_mutex_t mutex;

// void* routine() {
//     int i;
	
// 	i = 0;
// 	while(i < 10000000) 
// 	{
//         pthread_mutex_lock(&mutex);
//         mails++;
//         pthread_mutex_unlock(&mutex);
// 		i++;
// 	}
// }

// int main(int argc, char* argv[]) {
//     pthread_t th[4];
//     int i;
//     pthread_mutex_init(&mutex, NULL);
//    i = 1;
//    while ( i <= 4) 
//    {
//         if (pthread_create(th + i, NULL, &routine, NULL) != 0) {
//             perror("Failed to create thread");
//             return 1; //th + i same as th[i]
//    		}
// 		printf("Philo %d is awake\n", i);
// 		i++;
// 	}
// 	i = 1;
//     while (i < 4) 
// 	{
//         if (pthread_join(th[i], NULL) != 0) {
//             return 2;
//         }
//         printf("Philo %d has finished eating\n", i);
// 		i++;
//     }
//     pthread_mutex_destroy(&mutex);
//     printf("Number of mails: %d\n", mails);
//     return 0;
// } //the messages in main don't correspond to when thread actually finishes executing


/*DESCRIPTION OF THREAD_CREATE AND THREAD_JOIN ++ MUTEX FTS*/
// typedef struct s_data
// {
	
// 	pthread_t 		t1;	//place where api can store info about the thread
// 	pthread_t 		t2;
// }	t_data;

// pthread_mutex_t mutex;
// int mails = 0;

// void	*ft()
// {
// 	int i;

// 	i = 0;
// 	while (i < 10000000)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		mails++;
// 		pthread_mutex_unlock(&mutex);
// 		i++;
// 		//read mails
// 		//increment
// 		//write mails
// 	}
// 	return (0);
// }

// int main(int argc, char *argv[])
// {
// 	t_data	data;
// 	pthread_mutex_init(&mutex, NULL);
// 	pthread_create(&data.t1, NULL, (void *) &ft, NULL);
// 	pthread_create(&data.t2, NULL, (void *) &ft, NULL);
// 	//arg0 ptr to t1 var, hence &
// 	//arg1 customisation. Passing NULL will use defaults. Andrei used defaults
// 	//arg2 passes ft as argument, which is why you ref with &
// 	//arg3 arg passed into "routine" Andrei passed a struct

// 	/*need thread to finish execution first. Use ft below to check if thread is done*/
// 	pthread_join(data.t1, NULL);
// 	pthread_join(data.t2, NULL);
// 	//arg0 is thread to join
// 	//arg1 is pointer to return value of thread, NULL if not needed
// 	pthread_mutex_destroy(&mutex);
// 	printf("Number of mails: %d\n", mails);
// 	return 0;
// }
