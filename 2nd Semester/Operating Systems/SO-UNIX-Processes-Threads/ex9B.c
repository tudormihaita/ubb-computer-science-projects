#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 1024

int main(int argc, char* argv[]){
	char* fifo_a2b = "./fifoa2b";

	int fd = open(fifo_a2b, O_RDONLY);
	if(fd == -1){
		perror("Error on opening fifo!\n");
		exit(1);
	}

	char* buf = (char*)malloc(SIZE*sizeof(char));
	memset(buf,0,SIZE*sizeof(char));

	while(1){
		read(fd,buf,SIZE*sizeof(char));

		if(strlen(buf) == 0)
			break;

		printf("%s\n", buf);
		memset(buf,0,SIZE*sizeof(char));

	}

	free(buf);
	close(fd);

	return 0;
}
