#include <unistd.h>

void buffered_write(int chunk_size, int fd, char* buffer, int to_write){
	int w=0;
	while (to_write){
		if(to_write < chunk_size)
			chunk_size = 1;
		w = write(fd, buffer, chunk_size);
		to_write -= w;
		buffer += w;
	}	
}
