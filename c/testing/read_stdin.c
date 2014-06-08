#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 100

char *read_buffered(int chunk_size, int fd, int *bytes_read){
	int c = 0, t = 0, p = 0;
	char *buf = (char *) malloc(chunk_size * sizeof(char));	
	if (buf == NULL)
		return buf;
	for(;;){
		if((t = read(fd, buf+c, chunk_size)) == 0) 
			break;
		c += t;
		buf = (char *) realloc(buf, (chunk_size + (chunk_size * ++p)) * sizeof(char));
		if (buf == NULL)
			return buf;
	}
	*bytes_read = c;
	return buf;
}

void buffered_write(int chunk_size, int fd, char* buffer, int to_write){
	printf("Write:\n");
	int w=0;
	while (to_write){
		if(to_write < chunk_size)
			chunk_size = 1;
		w = write(fd, buffer, chunk_size);
		to_write -= w;
		buffer += w;
	}	
	printf("end\n");
}

int main(int argc, char *argv[]){
	int c = 0, t = 0;
	int p = 0;
	char *buf = read_buffered(MAX, STDIN_FILENO, &c);
	buffered_write(MAX, STDOUT_FILENO, buf, c);
	return EXIT_SUCCESS;
}

