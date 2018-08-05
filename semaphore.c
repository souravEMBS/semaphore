#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>

//pthread_mutex_t lock;
sem_t mutex;

void *myfunc1(void *n);
void *myfunc2(void *n);

int a[100];

int main(int argc, char const *argv[])
{
	/* code */

	int pthread1,pthread2;
	pthread_t thread1,thread2;
	char* msg1 = "first thread";
	char* msg2 = "second thread";

	int sem_ret;
	if((sem_ret = sem_init(&mutex,0,1)) != 0)
		perror("semaphore init error: ");

	if((pthread1 = pthread_create(&thread1,NULL,myfunc1,(void *)msg1)) != 0)
		perror("no thread with error no ");
	else
		perror("thread1: ");

	if((pthread2 = pthread_create(&thread2,NULL,myfunc2,(void *)msg2)) != 0)
		perror("no thread with error no ");
	else
		perror("thread2: ");

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	sem_destroy(&mutex);

	printf("thread 1 return: %d\nthread2 return %d\nsemaphore return %d\n"
		,pthread1,pthread2,sem_ret);
	
	return 0;
}

void *myfunc1(void *n){
	char* msg;
	msg = (char *)n;

	int i;

	sem_wait(&mutex);
	//pthread_mutex_lock(&lock);

	for(i=0;i<100;i++)
	{
		//sem_wait(&mutex);
		printf("W %d\n",i);
		a[i] = i;
		//sem_post(&mutex);
	}
	sem_post(&mutex);
	pthread_exit(0);

	//pthread_mutex_unlock(&lock);
}

void *myfunc2(void *n){
	char* msg;
	msg = (char *)n;

	int i;

	//pthread_mutex_lock(&lock);

	sem_wait(&mutex);

	for(i=0;i<100;i++)
	{
		//sem_wait(&mutex);
		printf("R %d\n",a[i]);
		//sem_post(&mutex);
	}

	sem_post(&mutex);
	pthread_exit(0);
	//pthread_mutex_unlock(&lock);

}
