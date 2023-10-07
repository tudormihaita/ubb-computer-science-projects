#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	srand(time(0));
	int n;
	int a2b[2], b2a[2];

	int res = pipe(a2b);
	if(res == -1){
		perror("Failed on pipe creation!\n");
		exit(1);
	}

	res = pipe(b2a);
	if(res == -1){
		perror("Failed on pipe creation!\n");
		exit(1);
	}

	while(1){
		n = 50 + rand() % (200-50);

		printf("Number sent to B is: %d\n", n);

		int pid = fork();
		if(pid == -1){
			perror("Failed on process creation!\n");
			exit(1);
		}
		if(pid == 0){
			close(a2b[1]);
			close(b2a[0]);

			int m;
			read(a2b[0], &m, sizeof(int));

			m/=2;

			write(b2a[1], &m, sizeof(int));

			close(a2b[0]);
			close(b2a[1]);

			exit(0);
		}

		if(n%2 == 0)
			write(a2b[1], &n, sizeof(int));
		else{
			n++;
			write(a2b[1], &n, sizeof(int));
		}

		read(b2a[0], &n, sizeof(int));

		printf("Number received from B is: %d\n", n);

		if(n < 40){
			printf("Number lower than 40 received, stopping...\n");
			break;
		}

		wait(0);

		sleep(1);
	}

	close(a2b[0]);
	close(a2b[1]);
	close(b2a[0]);
	close(b2a[1]);

	return 0;

}
