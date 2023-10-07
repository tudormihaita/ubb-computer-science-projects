#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	
	FILE* fd;
	int c2p[2];
	int k, N;
	
	if(argc < 2){
		perror("Numar invalid de argumente!\n");
		exit(EXIT_FAILURE);
	}

	fd = fopen(argv[1], "w");       

	int res = pipe(c2p);
	if(res == -1){
		perror("pipe c2p error");
		exit(EXIT_FAILURE);
	}

	int pid = fork();
	if(pid == -1){
		perror("fork error");
		exit(EXIT_FAILURE);
	}

	//child process
	if(pid == 0){
		close(c2p[0]);

		while(1){
			printf("k = ");
			scanf("%d", &k);

			write(c2p[1], &k, sizeof(int));

			if(k==0)
				break;

			N = rand() % 10;
			write(c2p[1], &N, sizeof(int));

		}

		close(c2p[1]);
		exit(EXIT_SUCCESS);

	}


	close(c2p[1]);

	while(1){
		read(c2p[0], &k, sizeof(int));

		if(k==0)
			break;

		read(c2p[0], &N, sizeof(int));

		//printf("%d %d\n", k, N);

		if(k==0)
			break;

		if(k%2==0){
			int sum = 0;
			int cpN = N;
			while(cpN){
				sum += cpN%10;
				cpN/=10;
			}

			fprintf(fd, "%d %d %d\n", k, N, sum);
		}
		else{
			int p=1;
			int cpN = N;
			while(cpN){
				p *= cpN%10;
				cpN/=10;
			}

			fprintf(fd, "%d %d %d\n", k, N, p);

		}

	}


	int status;
	wait(&status);
	printf("Child has finished with exit status: %d\n", status);

	close(c2p[0]);
	fclose(fd);

	return 0;

}
