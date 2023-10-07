#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]){
	char* fifoBA = "./fifoBA";
	char* fifoAB = "./fifoAB";

	srand(time(0));

	int res = mkfifo(fifoAB, 0666);
	if(res == -1){
		perror("Mkfifo error!\n");
		exit(1);
	}

	res = mkfifo(fifoBA, 0666);
	if(res == -1){
		perror("Mkfifo error!\n");
		exit(1);
	}

	int fdBA = open(fifoBA, O_WRONLY);
	if(fdBA == -1){	
	perror("Can't open fifo BA!\n");
		exit(1);
	}

	int fdAB = open(fifoAB, O_RDONLY);
	if(fdAB == -1){
		perror("Can't open fifo AB!\n");
		exit(1);
	}

	char semn;
	int Y;

	while(1){
		Y = 1000 + rand() % (10000 - 1000);
		write(fdBA, &Y, sizeof(int));

		read(fdAB, &semn, sizeof(char));

		printf("%d %c\n", Y, semn);

		if(semn == '=')
			break;
	}


	unlink(fifoAB);
	close(fdAB);
	close(fdBA);

	return 0;
}
