#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

int n, fr[10], sum = 0, closest = INT_MAX;
int* v;
float avg = 0;
pthread_t* threads;
pthread_mutex_t mtx;
pthread_barrier_t barr;

void* work(void* arg){
	int digit = *(int*)arg;
	free(arg);

	for(int i=0;i<n;i++){
		if(v[i] % 10 == digit)
			fr[digit]++;
	}

	pthread_mutex_lock(&mtx);
	sum+=fr[digit];
	pthread_mutex_unlock(&mtx);

	pthread_barrier_wait(&barr);

	avg = sum / 10;

	pthread_mutex_lock(&mtx);
	if(abs(avg - fr[digit]) < closest){
		closest = abs(avg - fr[digit]);
	}
	pthread_mutex_unlock(&mtx);

	printf("Computed frequency %2d of digit %2d; Average is %.4f\n", fr[digit], digit, avg);

	return NULL;
}


int main(int argc, char* argv[]){
	if(argc != 2){
		perror("Please provide one command line argument!\n");
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	v = (int*)malloc(n*sizeof(int));

	srand(time(NULL));
	for(int i=0;i<n;i++){
		int nr = rand() % 1000;
		v[i] = nr;
	}


	threads = (pthread_t*)malloc(10*sizeof(pthread_t));
	pthread_mutex_init(&mtx, NULL);
	pthread_barrier_init(&barr, NULL, 10);

	for(int i=0;i<10;i++){
		int* current = (int*)malloc(sizeof(int));
		*current = i;
		pthread_create(&threads[i], NULL, work, current);
	}

	for(int i=0;i<10;i++){
		pthread_join(threads[i], NULL);
	}

	printf("Threads finished...\n");
	sleep(2);

	for(int i=0;i<10;i++){
		if(abs(avg-fr[i]) == closest){
			printf("Digit %2d has the closest frequency of %2d to the average %.4f\n", i, fr[i], avg);
		}
	}

	printf("Parent done, stopping...\n");

	pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&barr);
	free(threads);
	free(v);

	return 0;
}
