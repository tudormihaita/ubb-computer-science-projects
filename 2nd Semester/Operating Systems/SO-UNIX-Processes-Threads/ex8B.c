#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	char* fifoa2b = "./myfifoa2b";
	char* fifob2a = "./myfifob2a";

	int fd_a2b = open(fifoa2b, O_RDONLY);
	if(fd_a2b == -1){
		perror("Error opening fifo a2b!\n");
		exit(1);
	}

	int fd_b2a = open(fifob2a, O_WRONLY);
	if(fd_b2a == -1){
		perror("Error opening fifo b2a!\n");
		exit(1);
	}

	while(1){
		int len;
		read(fd_a2b, &len, sizeof(int));

		if(len == -1)
			break;

		char* buf = (char*)malloc(len*sizeof(char));
		read(fd_a2b, buf, len);

		int i;
		for(i=0;i<len;i++){
			if(buf[i] >= 'a' && buf[i] <= 'z'){
				buf[i] = buf[i] -  ('a' - 'A');
			}
		}

		write(fd_b2a, buf, len);
		free(buf);
	}

	close(fd_a2b);
	close(fd_b2a);

	return 0;
}
