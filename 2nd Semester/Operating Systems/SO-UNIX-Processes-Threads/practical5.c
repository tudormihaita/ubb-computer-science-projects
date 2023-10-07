#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int is_prime(int n){
	if(n < 2)
		return 0;
	else if(n % 2 == 0 && n != 2)
		return 0;
	else{
		for(int d=3;d*d<=n;d+=2)
			if(n%d==0)
				return 0;
	}

	return 1;
}


int main(int argc, char* argv[]){
	if(argc < 2){
		perror("Provide at least one command line argument!\n");
		exit(EXIT_FAILURE);
		//printf("nu-i bun!\n");
		//return 1;
	}

	int a2b[2], b2c[2], c2p[2];

	int res = pipe(a2b);
	if(res == -1){
		perror("Failed on creating pipe!\n");
		exit(EXIT_FAILURE);
	}

	res = pipe(b2c);
	if(res == -1){
		perror("Failed on creating pipe!\n");
		exit(EXIT_FAILURE);
	}

	res = pipe(c2p);
	if(res == -1){
		perror("Failed on creating pipe!\n");
		exit(EXIT_FAILURE);
	}

	int pid = fork();
	if(pid == -1){
		perror("Failed on creating child process A!\n");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0){
		//child process A
		close(c2p[0]);
		close(c2p[1]);
		close(b2c[0]);
		close(b2c[1]);
		close(a2b[0]);

		for(int i=1;i<argc;i++){
			int n = atoi(argv[i]);
			if(is_prime(n) == 1)
				write(a2b[1], &n, sizeof(int));
		}

		close(a2b[1]);

		exit(0);
	}


	pid = fork();
		if(pid == -1){
			perror("Failed on creating child process B!\n");
			exit(EXIT_FAILURE);
		}
		else if(pid == 0){
			//child process B
			close(c2p[0]);
			close(c2p[1]);
			close(b2c[0]);
			close(a2b[1]);

			int max_prime = -1;
			int nr = -1;
			while(read(a2b[0], &nr, sizeof(int)) > 0){
				if(nr > max_prime)
					max_prime = nr;

			}
			
			printf("[IN CHILD B] Max prime number is: %d\n", max_prime);

			write(b2c[1], &max_prime, sizeof(int));

			close(a2b[0]);
			close(b2c[1]);

			exit(0);

		}




	pid = fork();
		if(pid == -1){
			perror("Failed on creating child process C!\n");
			exit(EXIT_FAILURE);

		}
		else if(pid == 0){
			//child process C
			close(c2p[0]);
			close(a2b[0]);
			close(a2b[1]);
			close(b2c[1]);

			int sum=0;
			int max_prime = 0;

			read(b2c[0], &max_prime, sizeof(int));

			while(max_prime){
				sum += max_prime % 10;
				max_prime /= 10;
			}

			write(c2p[1], &sum, sizeof(int));

			close(b2c[0]);
			close(c2p[1]);

			exit(0);

		}

		//parent process
		close(a2b[1]);
		close(a2b[0]);
		close(b2c[0]);
		close(b2c[1]);
		close(c2p[1]);

		int sum = 0;

		read(c2p[0], &sum, sizeof(int));

		printf("[IN PARENT] Sum of max prime number's digits is: %d\n", sum);

		wait(0);
		wait(0);
		wait(0);

		close(c2p[0]);

		return 0;
}
