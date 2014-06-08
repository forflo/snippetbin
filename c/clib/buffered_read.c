#include <unistd.h>
#include <stdlib.h>
#include "clibf.h"

/* reads <bytes_read> bytes from <fd>. It does that by reading chunks of <chunck_size> bytes
	Return: NULL if memory allocation failed. A valid Pointer on the Programs Heap */
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
