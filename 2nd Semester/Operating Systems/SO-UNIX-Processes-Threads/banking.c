#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

pthread_mutex_t mtx;
pthread_barrier_t barr;
pthread_cond_t cond;
pthread_t* producers;
pthread_t* consumers;
int nr_producers, nr_consumers, prod, consume;
int deposits;
int acc_value = 100;

void* deposit(void* arg){
	int id = *(int*)arg;
	id++;
	free(arg);
	printf("[DEPOSIT] Thread %2d created, waiting on minimum number of threads...\n", id);
	pthread_barrier_wait(&barr);
	printf("[DEPOSIT] Enough threads created, execution starting...\n");
	sleep(2);

	int deposit_value = prod * id;
	pthread_mutex_lock(&mtx);
	acc_value += deposit_value;
	deposits--;
	printf("[DEPOSIT] Thread %2d added deposit of %2d, new account value is %2d...\n", id, deposit_value, acc_value);
	sleep(1);

	if(acc_value >= 0)
		pthread_cond_signal(&cond);

	pthread_mutex_unlock(&mtx);

	return NULL;
}

void* withdraw(void* arg){
	int id = *(int*)arg;
	id++;
	free(arg);
	printf("[WITHDRAW] Thread %2d created, waiting on mininum number of threads...\n", id);
	pthread_barrier_wait(&barr);
	printf("[WITHDRAW] Enough threads created, execution starting...\n");
	sleep(2);

	int withdraw_value = consume * id;
	if(deposits > 0){
	pthread_mutex_lock(&mtx);
	while(acc_value - withdraw_value < 0){
		pthread_cond_wait(&cond, &mtx);
	}
	acc_value -= withdraw_value;
	printf("[WITHDRAW] Thread %2d decreased withdrawal of %2d, new account value is %2d...\n", id, withdraw_value, acc_value);
	sleep(1);

	pthread_mutex_unlock(&mtx);
	}
	else if(acc_value - withdraw_value >= 0){

		pthread_mutex_lock(&mtx);
		acc_value -= withdraw_value;
		printf("[WITHDRAW] Thread %2d decreased withdrawal of %2d, new account value is %2d...\n", id, withdraw_value, acc_value);
		sleep(1);
		pthread_mutex_unlock(&mtx);
	}
	else{
		printf("[WITHDRAW] Can't perform given withdrawal of %2d from account value %2d!\n", withdraw_value, acc_value);
	}

	return NULL;
}

int main(int argc, char* argv[]){
	if( argc != 5){
		perror("Please provide 4 numerical command line arguments!\n");
		exit(EXIT_FAILURE);
	}

	nr_producers = atoi(argv[1]);
	nr_consumers = atoi(argv[2]);
	prod = atoi(argv[3]);
	consume = atoi(argv[4]);

	producers = (pthread_t*)malloc(nr_producers*sizeof(pthread_t));
	consumers = (pthread_t*)malloc(nr_consumers*sizeof(pthread_t));

	pthread_mutex_init(&mtx, NULL);
	//minimum threads to be created in order to start deposits/withdrawals - minimum 5 of each
	pthread_barrier_init(&barr, NULL, nr_producers + nr_consumers);
	pthread_cond_init(&cond, NULL);
	
	int id_prod = 0, id_cons = 0;
	deposits = nr_producers;
	while(id_prod < nr_producers && id_cons < nr_consumers){
		int* id_deposit = (int*)malloc(sizeof(int));
		*id_deposit = id_prod;
		pthread_create(&producers[id_prod], NULL, deposit, id_deposit);
		id_prod++;

		int* id_withdrawal = (int*)malloc(sizeof(int));
		*id_withdrawal = id_cons;
		pthread_create(&consumers[id_cons], NULL, withdraw, id_withdrawal);
		id_cons++;
	}

	while(id_prod < nr_producers){
		int* id_deposit = (int*)malloc(sizeof(int));
		*id_deposit = id_prod;
		pthread_create(&producers[id_prod], NULL, deposit, id_deposit);
		id_prod++;
	}

	while(id_cons < nr_consumers){
		int* id_withdrawal = (int*)malloc(sizeof(int));
		*id_withdrawal = id_cons;
		pthread_create(&consumers[id_cons], NULL, withdraw, id_withdrawal);
		id_cons++;
	}

	for(int i=0;i<nr_producers;i++){
		pthread_join(producers[i], NULL);
	}
	for(int i=0;i<nr_consumers;i++){
		pthread_join(consumers[i], NULL);
	}

	printf("[MAIN] All threads finished execution, final value of account is %2d, stopping...\n", acc_value);

	free(producers);
	free(consumers);
	pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&barr);
	pthread_cond_destroy(&cond);

	return 0;
}
