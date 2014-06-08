#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#define EXIT(s) {fprintf(stderr, "%s", s); exit(EXIT_FAILURE); }
#define BUF PIPE_BUF*8
enum { ERROR = -1, SUCCESS};

int main(int argc, char **argv){
	int fd[2];
	pid_t pid;
	FILE *pipe_writer, *file;
	char buffer[PIPE_BUF];
	if (argc != 2){
		fprintf(stderr, "Usage %s <datei zum lesen>\n", *argv);
		exit(EXIT_FAILURE);
	}
	if ((file = fopen(argv[1], "r")) == NULL)
		EXIT ("Fehler bei fopen ...\n");
	if (pipe (fd) == ERROR)
		EXIT ("Fehler bei pipe ...\n");
	if ((pid = fork()) == ERROR)
		EXIT ("Fehler bei pipe ...\n");
	if (pid > 0){
		close (*fd);
		if ((pipe_writer = fdopen(*(fd+1), "w")) == NULL)
			EXIT ("Fehler bei fdopen ...\n");
		fread (buffer, PIPE_BUF, 1, file);
		fputs(buffer, pipe_writer);
		fclose(pipe_writer);
		if (waitpid(pid, NULL, 0) == ERROR)
			EXIT ("Fehler bei waitpid...\n");
		exit (EXIT_SUCCESS);
	} else {
		close(fd[1]);
		if(fd[1] != STDIN_FILENO){
			if (dup2 (*fd, STDIN_FILENO) != STDIN_FILENO)
				EXIT ("Fehler bei dup2...\n");
			close(*fd);
		}
		execl ("/usr/bin/less", "less", NULL);
			EXIT ("Fehler bei execl ...\n");
	}
	return EXIT_SUCCESS;
}
