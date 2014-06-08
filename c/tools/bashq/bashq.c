#include <stdio.h>
#include "def.h"

int main(int argc, char **argv){
	if(parse_args(argc, argv)){
		//Errorhandling
	}

	if(o_help()){
		
	} else if(o_version()){
	
	} else if(o_create() && o_key()){
		
	} else if(o_dest() && o_key()){
		
	} else if(o_send() && o_key()){
		
	} else if(o_recv() && o_key()){
		
	}
}

void usage(){
	printf("usage: %s\n", MSG_USAGE);
}
