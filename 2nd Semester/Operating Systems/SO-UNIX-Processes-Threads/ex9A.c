#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 1024

int main(int argc, char* argv[]){
	char* fifo_a2b = "./fifoa2b";
	FILE* f;

	int res = mkfifo(fifo_a2b, 0666);
	if(res == -1){
		perror("Error on making fifo!\n");
		exit(1);
	}

	int fd = open(fifo_a2b, O_WRONLY);
	if(fd == -1){
		perror("Error on opening fifo!\n");
		exit(1);
	}

	char* cmd = (char*)malloc(SIZE*sizeof(char));
	memset(cmd,0,SIZE*sizeof(char));

	char* buf = (char*)malloc(SIZE*sizeof(char));
	memset(buf,0,SIZE*sizeof(char));

	while(1){
		//using read from stdin(0) to get whitespaces too
		int k = read(0,cmd,SIZE*sizeof(char));
		if(k<0){
			perror("Error reading command!\n");
		}

		cmd[k-1]=0;
		if(strcmp(cmd, "stop") == 0){
			printf("Stopping...\n");
			break;
		}

		if((f=popen(cmd, "r")) == NULL){
			perror("Error on popen!\n");
		}
		else{
			//reading command output from stdout(1)
			fread(buf,1,SIZE-1,f);
			write(fd,buf,SIZE);
			memset(buf,0,SIZE*sizeof(char));
		}

		pclose(f);
		memset(cmd,0,SIZE*sizeof(char));
	}

	char* stop = (char*)malloc(SIZE*sizeof(char));
	memset(stop,0,SIZE*sizeof(char));

	write(fd,stop,SIZE);

	close(fd);
	free(cmd);
	free(buf);
	free(stop);

	unlink(fifo_a2b);

	return 0;
}
		

