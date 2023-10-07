#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int n, n1, n2;
	int p2c[2], c2p[2];

	printf("Give a number between 1 and 7: ");
	scanf("%d", &n);

	if(n <= 0 || n > 7){
		perror("Invalid number!\n");
		exit(EXIT_FAILURE);
	}

	int res = pipe(p2c);
	if(res == -1){
		perror("Failed on creating pipe!\n");
		exit(EXIT_FAILURE);
	}
	
	res = pipe(c2p);
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
		//child process
		close(p2c[1]);
		close(c2p[0]);

		while(1){
			read(p2c[0], &n, sizeof(int));
			if( n == -1){
				printf("[IN CHILD], Number given was greater than 1000, stopping...\n");
				break;
			}

			int n1 = n * 2;
			int n2 = n / 3;

			write(c2p[1], &n1, sizeof(int));
			write(c2p[1], &n2, sizeof(int));

		}

		close(p2c[0]);
		close(c2p[1]);

		exit(EXIT_SUCCESS);

	}

	//parent process
	close(p2c[0]);
	close(c2p[1]);

	write(p2c[1], &n, sizeof(int));

	while(1){
		//if(n >= 1000){
		//	int end = -1;
		//	write(p2c[1], &end, sizeof(int));
		//	break;
		//}

		read(c2p[0], &n1, sizeof(int));
		read(c2p[0], &n2, sizeof(int));

		n = n1 + n2;
		printf("[IN PARENT] New number given is %d, sending back to child...\n", n);
		sleep(1);

		if(n >= 1000){
			int end = -1;
			write(p2c[1], &end, sizeof(int));
			break;
		}
		
		write(p2c[1], &n, sizeof(int));
	}


	wait(0);

	close(c2p[0]);
	close(p2c[1]);

	return 0;

}
