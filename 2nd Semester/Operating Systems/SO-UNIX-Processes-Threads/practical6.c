#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		perror("Provide at least one command line argument!\n");
		exit(EXIT_FAILURE);
	}


	char* fifo_p2c = "./fifo_p2c";
	char* fifo_c2p = "./fifo_c2p";

	int res = mkfifo(fifo_p2c, 0666);
	if(res == -1){
		perror("Failed to create fifo!\n");
		exit(EXIT_FAILURE);
	}

	res = mkfifo(fifo_c2p, 0666);
	if(res == -1){
		perror("Failed to create fifo!\n");
		exit(EXIT_FAILURE);
	}

	int pid = fork();
	if(pid == -1){
		perror("Failed to create child process!\n");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0){
		//child process

		int sum = 0, p = 1;
		int n = 0;

		int fd_p2c = open(fifo_p2c, O_RDONLY);
		if(fd_p2c == -1){
			perror("Failed to open fifo!\n");
			exit(EXIT_FAILURE);
		}

		int fd_c2p = open(fifo_c2p, O_WRONLY);
		if(fd_c2p == -1){
			perror("Failed to open fifo!\n");
			exit(EXIT_FAILURE);
		}

		//while(read(fd_p2c, &n, sizeof(int)) > 0){
		while(1){
			read(fd_p2c, &n, sizeof(int));
			if(n == -1)
				break;

			printf("[IN CHILD] Current number : %d\n", n);

			if(n % 2 == 0)
				sum += n;
			else
				p *= n;
		}

		write(fd_c2p, &sum, sizeof(int));
		write(fd_c2p, &p, sizeof(int));

		close(fd_p2c);
		close(fd_c2p);

		unlink(fifo_p2c);
		unlink(fifo_c2p);

		exit(EXIT_SUCCESS);

	}

	//parent process
	
	int fd_p2c = open(fifo_p2c, O_WRONLY);
	if(fd_p2c == -1){
		perror("Failed to open fifo!\n");
		exit(EXIT_FAILURE);
	}

	int fd_c2p = open(fifo_c2p, O_RDONLY);
	if(fd_c2p == -1){
		perror("Failed to open fifo!\n");
		exit(EXIT_FAILURE);
	}

	for(int i=1;i<argc;i++){
		int nr = atoi(argv[i]);
		write(fd_p2c, &nr, sizeof(int));
	}

	int end = -1;
	write(fd_p2c, &end, sizeof(int));

	//close(fd_p2c);

	int sum, p;

	read(fd_c2p, &sum, sizeof(int));
	read(fd_c2p, &p, sizeof(int));

	printf("sum = %d; prod = %d\n", sum, p);

	wait(0);

	close(fd_c2p);
	close(fd_p2c);

	return 0;
}


