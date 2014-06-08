#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	int pip[2];
	FILE *file;
	pid_t pid;
	int status;

	if(pipe(pip)){
		exit(EXIT_FAILURE);
	}

	switch(pid = fork()){
		case -1:
			printf("Error in fork\n");
			exit(EXIT_FAILURE);
			break;
		case 0:
			printf("Im Kindprozess\n");
			close(pip[1]);	
			if(dup2(pip[0], 0) < 0)
				printf("Fehler im Kind\n");
			execlp("read_stdin", "read_stdin", NULL);
			printf("Konnte read_stdin nicht starten!\n");
			exit(EXIT_SUCCESS);
			break;
		default:
			close(pip[0]);
			file = fdopen(pip[1],"w");
			fprintf(file, "%s", "Dieser Text wurde vom Elternprozess gesendet\n");
			fclose(file);
			wait(&status);
			exit(EXIT_SUCCESS);
			break;
	}
}
