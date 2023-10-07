#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>

pthread_mutex_t mtx;
pthread_barrier_t barr;
pthread_t* workers;
pthread_t reader;
int n, fr[100], sum = 0, min = INT_MAX;
int* v;
int thr_num = 0;
float avg;

int prim(int n){
	if(n < 2)
		return 0;
	else if(n % 2 == 0 && n != 2)
		return 0;
	else{
		for(int d=3;d*d<=n;d+=2)
			if(n % d == 0)
				return 0;
	}

	return 1;

}

void* file_read(void* arg){
	/*
	int fd = open("random-file", O_RDONLY);
	for(int i=0;i<n;i++){
		read(fd, &v[i], sizeof(int));
	}*/
	
	srand(time(NULL));
	for(int i=0;i<n;i++){
		int nr = rand() % 1001;
		v[i] = nr;
	}

	//close(fd);

	for(int i=2;i<100;i++){
		if(prim(i))
			thr_num++;
	}
	return NULL;
}

void* work(void* arg){
	int prime = *(int*)arg;
	free(arg);

	for(int i=0;i<n;i++){
		if(v[i] == prime)
			fr[prime]++;
	}

	pthread_mutex_lock(&mtx);
	sum+=fr[prime];
	pthread_mutex_unlock(&mtx);

	pthread_barrier_wait(&barr);
	
	avg = sum / thr_num;
	//printf("Average is: %.6f\n", avg);

	pthread_mutex_lock(&mtx);
	if(abs(avg - fr[prime]) < min)
	       min = abs(avg - fr[prime]);
	pthread_mutex_unlock(&mtx);

		
	return NULL;
}


int main(int argc, char* argv[]){
	if(argc < 2){
		perror("Please provide one command line argument!\n");
		exit(1);
	}

	n = atoi(argv[1]);
	v = (int*)malloc(n*sizeof(int));
	int count = -1;

	pthread_create(&reader,NULL,file_read,NULL);
	pthread_join(reader, NULL);

	pthread_mutex_init(&mtx, NULL);
	pthread_barrier_init(&barr, NULL, thr_num);

	workers = (pthread_t*)malloc(thr_num*sizeof(pthread_t));

	for(int i=2;i<100;i++){
		int* prime = (int*)malloc(sizeof(int));
		*prime = i;
		if(prim(i))
			pthread_create(&workers[++count], NULL, work, prime);
	}

	for(int i=0;i<thr_num;i++){
		pthread_join(workers[i], NULL);
	}

	for(int i=0;i<100;i++){
		if(prim(i) && abs(avg  - fr[i]) == min)
			printf("Frequency %2d of number %2d is closest to average %.6f\n", fr[i], i, avg);
	}

	pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&barr);
	free(workers);
	free(v);

	return 0;
}

