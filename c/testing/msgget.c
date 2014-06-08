#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void){
	int i = msgget((key_t) 123123, IPC_CREAT);
	return 0;
}
