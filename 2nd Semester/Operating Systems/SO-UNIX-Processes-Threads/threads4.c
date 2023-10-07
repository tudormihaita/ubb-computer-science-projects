#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

int* v;
int X,Y,ind=-1;
pthread_t* generators;
pthread_t* readers;
pthread_rwlock_t rwl;

void* generate(void* arg){
	int tid = *(int*)arg;
	free(arg);
	tid++;

	int i;
	for(i=0;i<X;i++){
		pthread_rwlock_wrlock(&rwl);
		int N = (i*Y) + (X/tid);
		ind++;
		v[ind] = N;
		pthread_rwlock_unlock(&rwl);
	}

	pthread_rwlock_wrlock(&rwl);
	ind++;
	v[ind] = 0;
	pthread_rwlock_unlock(&rwl);

	return NULL;
}

void* display(void* arg){
	int parity = *(int*)arg;
	free(arg);

	int rind = 0;
	int cnt = 0;
	int sum = 0;
	while(rind <= ind){
		pthread_rwlock_rdlock(&rwl);
		if(v[rind] != 0 && v[rind] % 2 == parity)
			sum+=v[rind];
		else if(v[rind] == 0)
			cnt++;

		if(cnt == 5)
			break;

		rind++;
		pthread_rwlock_unlock(&rwl);
	}

	if(parity == 0){
		printf("Sum of even numbers is: %d\n", sum);
	}
	else{
		printf("Sum of odd numbers is: %d\n", sum);
	}
	pthread_rwlock_unlock(&rwl);

	return NULL;
}

int main(int argc, char* argv[]){
	if(argc != 3){
		perror("Please provide 2 numerical command line arguments!\n");
		exit(EXIT_FAILURE);
	}

	X = atoi(argv[1]);
	Y = atoi(argv[2]);
	if(X < 0 || Y < 0){
		perror("Please provide 2 positive command line arguments!\n");
		exit(EXIT_FAILURE);
	}

	v=(int*)malloc(5*(X+1)*sizeof(int));
	generators=(pthread_t*)malloc(5*sizeof(pthread_t));
	readers=(pthread_t*)malloc(2*sizeof(pthread_t));

	pthread_rwlock_init(&rwl, NULL);
	for(int i=0;i<5;i++){
		int* id=(int*)malloc(sizeof(int));
		*id = i;
		pthread_create(&generators[i], NULL, generate, id);
	}

	for(int i=0;i<2;i++){
		int* parity=(int*)malloc(sizeof(int));
		*parity = i;
		pthread_create(&readers[i], NULL, display, parity);
	}

	for(int i=0;i<5;i++){
		pthread_join(generators[i], NULL);
	}
	for(int i=0;i<2;i++){
		pthread_join(readers[i], NULL);
	}
	for(int i=0;i<=ind;i++){
		//if(v[i]!=0)
		printf("%d ", v[i]);
	}
	printf("\n");
	pthread_rwlock_destroy(&rwl);
	free(generators);
	free(readers);

	return 0;

}
