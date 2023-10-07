#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>

#define INTERVAL 3000

int n, thr_num;
int* v;
float* mins;
float min;
pthread_t* workers;
pthread_t reader;
pthread_mutex_t mtx;
pthread_barrier_t barr;

void* generate(void* arg){
	srand(time(NULL));
	for(int i=0;i<n;i++){
		int nr = rand() % 1000;
		v[i] = nr;
	}

	printf("Generated %2d numbers...\n", n);
	sleep(1);

	return NULL;
}


void* work(void* arg){
	int id = *(int*)arg;
	free(arg);

	int start = id*INTERVAL;
       	int finish = start + INTERVAL;

	int sum = 0;
	for(int i=start;i<finish;i++){
		sum += v[i];
	}

	float avg = (float)sum / INTERVAL;

	int m = rand() % 256;

	mins[id]=fabs(avg - m);

	printf("Thread %2d: Difference between average %.4f and random generated number %2d is %2.4f\n", id, avg, m, mins[id]);

	pthread_barrier_wait(&barr);

	min = mins[0];
	for(int i=1;i<thr_num;i++){
		pthread_mutex_lock(&mtx);
		if(mins[i] < min)
			min = mins[i];
		pthread_mutex_unlock(&mtx);
	}

	printf("Thread %2d computed global minimum difference %2.4f...\n", id, min);
	return NULL;
}


int main(int argc, char* argv[]){
	if(argc != 2){
		perror("Please provide one command line argument!\n");
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	thr_num = n / INTERVAL;

	v = (int*)malloc(n*sizeof(int));
	pthread_create(&reader, NULL, generate, NULL);
	pthread_join(reader, NULL);

	pthread_mutex_init(&mtx, NULL);
	pthread_barrier_init(&barr, NULL, thr_num);


	mins = (float*)malloc(thr_num*sizeof(float));
	workers = (pthread_t*)malloc(thr_num*sizeof(pthread_t));
	for(int i=0;i<thr_num;i++){
		int* id = (int*)malloc(sizeof(int));
		*id = i;
		pthread_create(&workers[i], NULL, work, id);
	}

	for(int i=0;i<thr_num;i++){
		pthread_join(workers[i], NULL);
	}

	sleep(1);
	printf("Threads finished, global minimum difference is %2.4f, stopping...\n", min);

	pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&barr);
	free(workers);
	free(mins);
	free(v);


	return 0;
}

