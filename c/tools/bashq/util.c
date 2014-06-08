#include "def.h"
#include <unistd.h>
#include <stdlib.h>

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

void write_buffered(int chunk_size, int fd, char* buffer, int to_write){
	int w=0;
	while (to_write){
		if(to_write < chunk_size)
			chunk_size = 1;
		w = write(fd, buffer, chunk_size);
		to_write -= w;
		buffer += w;
	}	
}
