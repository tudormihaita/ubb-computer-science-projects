#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_BUF 101

int main(int argc, char* argv[]){
	char* fifo_a2b = "./fifo_a2b";
	char* fifo_b2a = "./fifo_b2a";
	char* fifo_p2a = "./fifo_p2a";


	int res = mkfifo(fifo_p2a, 0666);
	if(res == -1){
		perror("Failed to create fifo p2a!\n");
		exit(EXIT_FAILURE);
	}


	res = mkfifo(fifo_a2b, 0666);
	if(res == -1){
		perror("Failed to create fifo a2b!\n");
		exit(EXIT_FAILURE);
	}

	res = mkfifo(fifo_b2a, 0666);
	if(res == -1){
		perror("Failed to create fifo b2a!\n");
		exit(EXIT_FAILURE);
	}


	int pid = fork();
	if(pid == -1){
		perror("Failed on forking process!\n");
		exit(EXIT_FAILURE);
	}
	if(pid == 0){
		//child process A
		
		int fd_p2a = open(fifo_p2a, O_RDONLY);
		if(fd_p2a == -1){
			perror("[IN CHILD A] Failed on opening fifo p2a!\n");
			exit(EXIT_FAILURE);
		}


		int fd_a2b = open(fifo_a2b, O_WRONLY);
		if(fd_a2b == -1){
			perror("[IN CHILD A] Failed on opening fifo a2b!\n");
			exit(EXIT_FAILURE);
		}

		int fd_b2a = open(fifo_b2a, O_RDONLY);
		if(fd_b2a == -1){
			perror("[IN CHILD A] Failed on opening fifo b2a!\n");
			exit(EXIT_FAILURE);
		}

		int len;
		char* string;
		int valid = 1;

		read(fd_p2a, &len, sizeof(int));
		
		string = (char*)malloc(len*sizeof(char));

		read(fd_p2a, string, len);

		if(len < 4){
			int end = -1;
			write(fd_a2b, &end, sizeof(int));
			valid = 0;
		}

		if(valid){
			write(fd_a2b, &len, sizeof(int));
			write(fd_a2b, string, len);

			free(string);

			while(1){
				read(fd_b2a, &len, sizeof(int));
				
				string = (char*)malloc(len*sizeof(char));

				read(fd_b2a, string, len);

				if(len < 4){
					int end = -1;
					printf("[IN CHILD A] New string is: %s, shorter than 3 characters, stopping...\n", string);
					write(fd_a2b, &end, sizeof(int));
					free(string);
					break;
				}

				string[len-2] = '\0';

				len--;

				printf("[IN CHILD A] New string after removing last character is: %s, sending back to child B...\n", string);

				write(fd_a2b, &len, sizeof(int));

				write(fd_a2b, string, len);

				free(string);

				sleep(2);

			}
		}

			close(fd_p2a);
			close(fd_a2b);
			close(fd_b2a);

			unlink(fifo_p2a);

			exit(EXIT_SUCCESS);

	}


	pid = fork();
	if(pid == -1){
		perror("Failed on forking process!\n");
		exit(EXIT_FAILURE);
	}

	if(pid == 0){
		//child process B
		int fd_a2b = open(fifo_a2b, O_RDONLY);
		if(fd_a2b == -1){
			perror("[IN CHILD B] Failed on opening pipe a2b!\n");
			exit(EXIT_FAILURE);
		}

		int fd_b2a = open(fifo_b2a, O_WRONLY);
		if(fd_b2a == -1){
			perror("[IN CHILD B] Failed on opening pipe b2a!\n");
			exit(EXIT_FAILURE);
		}

		int len;
		char* string;

		while(1){
			read(fd_a2b, &len, sizeof(int));

			if(len == -1){
				printf("[IN CHILD B] String recieved is shorter than 3 characters, stopping...\n");
				break;
			}

			string = (char*)malloc(len*sizeof(char));

			read(fd_a2b, string, len);

			strcpy(string, string+2);

			printf("[IN CHILD B] New string after removing first 2 characters: %s, sending back to child A...\n", string);

			len -= 2;
			
			write(fd_b2a, &len, sizeof(int));
			write(fd_b2a, string, len);

			free(string);

			sleep(2);

		}

		close(fd_a2b);
		close(fd_b2a);

		unlink(fifo_a2b);
		unlink(fifo_b2a);

		exit(EXIT_SUCCESS);
	}

	//parent process	
					

	int fd_p2a = open(fifo_p2a, O_WRONLY);
	if(fd_p2a == -1){
		perror("Error on opening pipe p2a!\n");
		exit(EXIT_FAILURE);
	}

	printf("Enter the given string: ");

	char* string = (char*)malloc(MAX_BUF*sizeof(char));

	scanf("%s", string);

	int size = strlen(string) + 1;
	
	printf("[IN PARENT] Initial string is: %s, sending it to child processes...\n", string);

	write(fd_p2a, &size, sizeof(int));

	write(fd_p2a, string, size);
	
	wait(0);
	wait(0);

	free(string);

	sleep(2);

	close(fd_p2a);

	return 0;
}


