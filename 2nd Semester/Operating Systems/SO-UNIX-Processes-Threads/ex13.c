#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int N;

	printf("Enter the amount of integers to be read:");
	scanf("%d", &N);

	if(N <= 0){
		perror("Enter a valid amount of integers!\n");
		exit(EXIT_FAILURE);
	}

	int a2b[2], b2c[2], c2a[2];

	int res = pipe(a2b);
	if(res == -1){
		perror("Failed on creating pipe!\n");
		exit(EXIT_FAILURE);
	}

	res = pipe(b2c);
	if(res == -1){
		perror("Failed on creating pipe!\n");
		exit(EXIT_FAILURE);
	}

	res = pipe(c2a);
	if(res == -1){
		perror("Failed on creating pipe!\n");
		exit(EXIT_FAILURE);
	}

	int pid = fork();
	if(pid == -1){
		perror("Failed on forking process!\n");
		exit(EXIT_FAILURE);
	}

	if(pid == 0){
		//process B
		close(a2b[1]);
		close(b2c[0]);
		close(c2a[0]);
		close(c2a[1]);

		srand(time(NULL));

		int X;
		for(int i=0;i<N;i++){
			read(a2b[0], &X, sizeof(int));

			int randX = 2 + rand() % 4;
			randX += X;

			printf("[IN B] Received %d from A, sending %d to C...\n", X, randX);

			write(b2c[1], &randX, sizeof(int));

			sleep(1);

		}

		close(a2b[0]);
		close(b2c[1]);

		exit(EXIT_SUCCESS);

	}

	pid = fork();
	if(pid == -1){
		perror("Failed on forking process!\n");
		exit(EXIT_FAILURE);
	}

	if(pid == 0){
		//process C
		close(a2b[0]);
		close(a2b[1]);
		close(b2c[1]);
		close(c2a[0]);

		int sum = 0;
		int X;

		for(int i=0;i<N;i++){
			read(b2c[0], &X, sizeof(int));

			sum += X;

			printf("[IN C] Received %d from B, current sum is %d...\n", X, sum);

			sleep(1);
		}

		printf("[IN C] Final sum is %d, sending back to A...\n", sum);
		write(c2a[1], &sum, sizeof(int));

		close(b2c[0]);
		close(c2a[1]);

		exit(EXIT_SUCCESS);

	}

	//process A
	close(a2b[0]);
	close(b2c[0]);
	close(b2c[1]);
	close(c2a[1]);

	printf("Input %d integers:", N);

	int X;
	for(int i=0;i<N;i++){
		scanf("%d", &X);
		printf("[IN A] Sending %d to process B...\n", X);
		write(a2b[1], &X, sizeof(int));

		sleep(1);
	}


	int sum;
	read(c2a[0], &sum, sizeof(int));

	printf("[IN A] Received final sum of %d from process C, stopping...\n", sum);

	wait(0);
	wait(0);

	close(a2b[1]);
	close(c2a[0]);


	return 0;
}
