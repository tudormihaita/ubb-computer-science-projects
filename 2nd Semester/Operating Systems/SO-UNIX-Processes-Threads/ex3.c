#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BUF 1024

int main(int argc, char* argv[]){
	if(argc < 2){
		perror("Numar invalid de argumente!\n");
		exit(1);
	}

	FILE* fd;
	char c;
	char cuv[MAX_BUF];
	int p2c[2];

	fd = fopen(argv[1], "r");
	if(!fd){
		perror("Nu s-a putut deschide fisierul!\n");
		exit(1);
	}

	int res = pipe(p2c);
	if(res == -1){
		perror("Pipe creation error!\n");
		exit(1);
	}

	int pid = fork();
	if(pid == -1){
		perror("Fork process creation error!\n");
		exit(1);
	}

	//child process
	if(pid == 0){
		close(p2c[1]);

		while(1){
			read(p2c[0], &c, sizeof(char));
			
			if(c == '$')
				break;

			read(p2c[0], cuv, MAX_BUF);

			int pos = -1;
			for(int i=0; i<strlen(cuv) && pos == -1;i++){
				if(cuv[i] == c){
					pos = i;
				}
			}

			printf("%c %s %d\n", c, cuv, pos);

		}

		close(p2c[0]);

		wait(0);
	}

	//parent process
	close(p2c[0]);

	while(fscanf(fd, "%c %s\n", &c, cuv) != -1){
		write(p2c[1], &c, sizeof(char));
		write(p2c[1], cuv, MAX_BUF);
	}

	c = '$';
	write(p2c[1], &c, sizeof(char));


	wait(0);

	close(p2c[1]);

	fclose(fd);

	return 0;
}

