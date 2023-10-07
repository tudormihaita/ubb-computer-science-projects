#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BUF 1024

int main(int argc, char* argv[]){
	char* C;
	char* L;
	char* U;
	int S;

	int p2a[2], a2p[2], a2b[2];

	pipe(p2a);
	pipe(a2p);
	pipe(a2b);

	C = (char*)malloc(MAX_BUF*sizeof(char));

	while(1){
		scanf("%s", C);

		if(strcmp(C,"X") == 0)
			break;
		S=0;

		//child process A
		if(fork() == 0){
			close(p2a[1]);
			close(a2p[0]);
			close(a2b[0]);

			read(p2a[0], C, MAX_BUF);

			L = (char*)malloc(MAX_BUF*sizeof(char));
			U = (char*)malloc(MAX_BUF*sizeof(char));

			int i,j=0,k=0;
			for(i=0;i<strlen(C);i++){
				if(C[i] >= 'A' && C[i] <= 'Z')
					U[j++] = C[i];
				else if(C[i] >= 'a' && C[i] <= 'z')
					L[k++] = C[i];
				else
					S++;

			}

			write(a2p[1], &S, sizeof(int));

			write(a2b[1], L, MAX_BUF);
			write(a2b[1], U, MAX_BUF);

			free(L);
			free(U);
			free(C);

			close(p2a[0]);
			close(a2p[1]);
			close(a2b[1]);

			exit(0);
		}

		//child process B
		if(fork() == 0){
			close(p2a[0]);
			close(p2a[1]);
			close(a2b[1]);
			close(a2p[0]);
			close(a2p[1]);

			L = (char*)malloc(MAX_BUF*sizeof(char));
			U = (char*)malloc(MAX_BUF*sizeof(char));

			read(a2b[0], L, MAX_BUF);
			read(a2b[0], U, MAX_BUF);

			int size = strlen(L) + strlen(U);
			int sizeU = strlen(U);
			int sizeL = strlen(L);

			printf("[IN B] Size of L = %d\n", sizeL);
			printf("[IN B] Size of U = %d\n", sizeU);
			printf("[IN B] Size of L+U = %d\n", size);

			free(L);
			free(U);
			free(C);	

			close(a2b[0]);

			exit(0);
		}



		write(p2a[1], C, MAX_BUF);

		read(a2p[0], &S, sizeof(int));

		printf("[IN PARENT] S = %d\n", S);

		wait(0);
		wait(0);

	}

	free(C);

	close(a2p[0]);
	close(a2p[1]);
	close(a2b[0]);
	close(a2b[1]);
	close(p2a[0]);
	close(p2a[1]);

	return 0;

}
			

