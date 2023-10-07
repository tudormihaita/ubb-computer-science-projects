#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	//srand(time(NULL));

	int a2b[2], b2a[2];

	int res = pipe(a2b);
	if(res == -1){
		perror("Failed on creating pipe!\n");
		exit(EXIT_FAILURE);
	}

	res = pipe(b2a);
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
		//child process B
		close(a2b[1]);
		close(b2a[0]);

		srand(time(NULL));

		int B = 50 + rand() % 1000;
		int A;

		printf("Process B has generated %d\n", B);

		while(1){
			read(a2b[0], &A, sizeof(int));

			int dif;
			if(A > B){
				dif = A - B;
			}
			else{
			       	dif = B - A;
			}

			printf("B received %d; difference: %d\n", A, dif);

			write(b2a[1], &dif, sizeof(int));

			if(dif < 50)
				break;

		}

		close(a2b[0]);
		close(b2a[1]);

		exit(EXIT_SUCCESS);
	}

	//parent process A
	
	close(a2b[0]);
	close(b2a[1]);

	int count = 0;
	int dif, A;

	while(1){
		A = 50 + rand() % 1000;
		write(a2b[1], &A, sizeof(int));
		count++;

		read(b2a[0], &dif, sizeof(int));

		if(dif < 50){
			printf("Process A has %d numbers\n", count);
			break;
		}

		sleep(1);
	}

	wait(0);

	close(a2b[1]);
	close(b2a[0]);	

	return 0;
}
