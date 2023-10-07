#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BUF 101

int main(int argc, char* argv[]){
	if(argc < 2){
		perror("Provide at least one command line argument!\n");
		exit(EXIT_FAILURE);
	}

	/*int p2c[2];

	int res = pipe(p2c);
	if(res == -1){
		perror("Failed on creating pipe!\n");
		exit(EXIT_FAILURE);
	}*/

	for(int i=1;i<argc;i++){
		int pid = fork();
		if(pid == -1){
			perror("Failed on forking process!\n");
			exit(EXIT_FAILURE);
		}

		if(pid == 0){
			//child process
			FILE* f;
			f=fopen("in.txt", "a");

			int len = strlen(argv[i]);
			fprintf(f,"%s %d\n", argv[i], len);

			fclose(f);

			exit(EXIT_SUCCESS);
		}

		wait(0);

	}

	//parent process
	FILE* f;

	f=fopen("in.txt", "r");

	int len;
	char* arg = (char*)malloc(MAX_BUF*sizeof(char));

	while(fscanf(f,"%s %d\n", arg, &len) != -1){
	       if(len > 7){
	       		printf("%s longer than 7 characters\n", arg);
	       }

	}

	fclose(f);

	return 0;
}	

