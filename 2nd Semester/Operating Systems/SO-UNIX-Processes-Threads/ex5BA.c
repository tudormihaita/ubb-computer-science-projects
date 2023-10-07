#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]){
	char* fifoBA = "./fifoBA";
	char* fifoAB = "./fifoAB";

	srand(time(0));

	//int res = mkfifo(fifoBA, 0666);
	//if(res == -1){
	//	perror("Mkfifo error!\n");
	//	exit(1);
	//}

	int fdBA = open(fifoBA, O_RDONLY);
	if(fdBA == -1){
		perror("Can't open fifo BA!\n");
		exit(1);
	}

	int fdAB = open(fifoAB, O_WRONLY);
	if(fdAB == -1){
	perror("Can't open fifo AB!\n");
		exit(1);
	}

	char semn;
	int X,Y;
	X = 1000 + rand() % (10000-1000);
	printf("%d\n", X);

	while(1){
		read(fdBA, &Y, sizeof(int));

		if(X == Y){
			semn = '=';
			write(fdAB, &semn, sizeof(char));
			break;
		}
		else if(Y < X){
			semn = '<';
			write(fdAB, &semn, sizeof(char));
		}
		else if(Y > X){
			semn = '>';
			write(fdAB, &semn, sizeof(char));
		}

	}


	unlink(fifoBA);
	close(fdBA);
	close(fdAB);

	return 0;
}
		
	

	


