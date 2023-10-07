#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	if(argc < 2 || argc >= 10){
		perror("Provide between 1 and 9 command line arguments!\n");
		exit(EXIT_FAILURE);
	}

	int p2c[2], c2p[2];
	int size=0;

	for(int i=1;i<argc;i++)
		size =  size + strlen(argv[i]) + 1;
	
	char* rez = (char*)malloc(size*sizeof(char));
	memset(rez,0,size);

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

	for(int i=1;i<argc;i++){
		int pid = fork();
		if(pid == -1){
			perror("Failed on forking process!\n");
			exit(EXIT_FAILURE);
		}

		//child process
		if(pid == 0){
			int len=0;

			close(c2p[0]);
			close(p2c[1]);

			read(p2c[0], &len, sizeof(int));

			char* arg = (char*)malloc(len*sizeof(char));

			read(p2c[0], arg, len);

			for(int j=0;j<strlen(arg);j++){
				if(arg[j] >= 'a' && arg[j] <= 'z')
					arg[j] = arg[j] - ('a' - 'A');

			}

			write(c2p[1], arg, len);

			free(arg);

			close(p2c[0]);
			close(c2p[1]);

			exit(EXIT_SUCCESS);

		}

		//parent process
		int len = strlen(argv[i]) + 1;

		write(p2c[1], &len, sizeof(int));

		write(p2c[1], argv[i], len);

		//printf("Current arg: %s\n", argv[i]);

		char* converted = (char*)malloc(len*sizeof(char));
		read(c2p[0], converted, len);

		//printf("Converted arg: %s\n", converted);

		wait(0);

		strcat(rez, converted);
		strcat(rez, " ");

		free(converted);

	}

	printf("The result string is: %s\n", rez);

	free(rez);

	close(p2c[0]);
	close(p2c[1]);
	close(c2p[0]);
	close(c2p[1]);

	return 0;
}

