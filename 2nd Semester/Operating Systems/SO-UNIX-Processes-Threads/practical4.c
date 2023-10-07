#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 100

int main(int argc, char* argv[]){
	if(argc < 2){
		perror("Provide at least one command line argument!\n");
		exit(1);
	}

	int p2c[2];
	int res = pipe(p2c);
	if(res == -1){
		perror("Failed to create pipe!\n");
		exit(-1);
	}

	for(int i=1;i<argc;i++){
		int pid = fork();
		if(pid == -1){
			perror("Failed to fork process!\n");
			exit(1);
		}
		//child process
		if(pid == 0){
			close(p2c[1]);

			int len;
			read(p2c[0], &len, sizeof(int));

			char* cmd = (char*)malloc(len*sizeof(char));
			char* cpy_cmd = (char*)malloc(len*sizeof(char));

			read(p2c[0], cmd, len);

			strcpy(cpy_cmd, cmd);

			//printf("%s\n", cmd);

			int nr_args = 0;

			char* p = strtok(cmd, " ");
			while(p){
				nr_args++;
				p=strtok(NULL," ");
			}

			//printf("Nr args: %d\n", nr_args);

			char** args = (char**)malloc((nr_args+1)*sizeof(char*));

			char* q = strtok(cpy_cmd, " ");
			int len_cmd = strlen(q) + 1;
			char* name_cmd = (char*)malloc(len_cmd*sizeof(char));
			strcpy(name_cmd, q);

			int nr = 0;

			//printf("%s\n", cmd);
			while(q){
				len_cmd = strlen(q) + 1;
				args[nr] = (char*)malloc(len_cmd*sizeof(char));
				strcpy(args[nr], q);
				printf("%s\n", args[nr]);
				nr++;
				q=strtok(NULL, " ");
			}

			args[nr] = NULL;

			int runs = 0;
			//printf("Give the number of runs for the current command:\n");
			scanf("%d", &runs);

			for(int j=0;j<runs;j++){
				if(fork() == 0){
					if(execvp(name_cmd, args) == -1){
						perror("Exec failed!\n");
						exit(1);
					}

				exit(1);
				}

				wait(0);
			}

			free(cmd);
			free(cpy_cmd);
			free(name_cmd);
			for(int j=0;j<nr;j++)
				free(args[j]);

			free(args);

			close(p2c[0]);

			exit(0);

		}


		int len = strlen(argv[i]) + 1;
		char* cmd = (char*)malloc(len*sizeof(char));

		strcpy(cmd, argv[i]);

		printf("Current command to execute is: %s\n", cmd);

		write(p2c[1], &len, sizeof(int));

		write(p2c[1], cmd, len);
		
		wait(0);
		free(cmd);

		sleep(1);

	}


	close(p2c[0]);
	close(p2c[1]);


	return 0;	

}
