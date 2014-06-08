#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void call_gcc();

int main(int argc, char **argv, char **envp){
	call_gcc(envp);
}

void call_gcc(char **envp){
	pid_t pid;
	switch (pid=fork()){
		case -1:
			printf("Ein kritischer Fehler der Prozessgenerierung ist aufgetreten!\n");
			exit(1);
		break;
		case 0:
			printf("Starte GCC\n");
			char *args[] = {
				"/usr/bin/gcc",
				"-o",
				"/Users/florian/Desktop/test",
				"/Users/florian/Desktop/test.c",
				NULL
			};
			execve("/usr/bin/gcc", args, envp);	
		break;
		default:
			printf("Sie befinden sich im Elternprozess\n");
		break;
	}
}
