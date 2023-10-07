#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		perror("Provide at least 1 command line argument!\n");
		exit(1);
	}

	char* fifoa2b = "./myfifoa2b";
	char* fifob2a = "./myfifob2a";

	int res = mkfifo(fifoa2b, 0666);
	if(res == -1){
		perror("Error on making fifo a2b!\n");
		exit(1);
	}

	res = mkfifo(fifob2a, 0666);
	if(res == -1){
		perror("Error on making fifo b2a!\n");
		exit(1);
	}

	int fd_a2b = open(fifoa2b, O_WRONLY);
	if(fd_a2b == -1){
		perror("Error on opening fifo a2b!\n");
		exit(1);
	}

	int fd_b2a = open(fifob2a, O_RDONLY);
	if(fd_b2a == -1){
		perror("Error on opening fifo b2a!\n");
		exit(1);
	}

	int i, size = 0;
	for(i=1;i<argc;i++){
		size += strlen(argv[i]) + 1;
		size++; //for spaces between arguments
	}

	char* rez = (char*)malloc(size*sizeof(char));
	memset(rez,0,size*sizeof(char));

	for(i=1;i<argc;i++){
		int len = strlen(argv[i]) + 1;
		write(fd_a2b, &len, sizeof(int));
		write(fd_a2b, argv[i], len);

		char* buf = (char*)malloc(len*sizeof(char));
		memset(buf,0,len*sizeof(char));

		read(fd_b2a,buf,len);

		strcat(rez, buf);
		strcat(rez, " ");
		free(buf);

	}

	int stop = -1;
	write(fd_a2b, &stop, sizeof(int));

	printf("The result is: %s\n", rez);
	free(rez);

	close(fd_a2b);
	close(fd_b2a);

	unlink(fifoa2b);
	unlink(fifob2a);

	return 0;

}

		




