#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char **argv){
	int status, s;
	struct addrinfo *addr, *p;
	struct addrinfo hint;
	char ipstr[INET6_ADDRSTRLEN];
	const char *ty = "Thank you for calling!\n";

	memset(&hint, 0, sizeof (struct addrinfo));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;
	
	if(status = getaddrinfo(NULL, "7779", &hint, &addr)){
		fprintf(stderr, "[Error]%s\n", gai_strerror(status));
		exit(1);
	}

	printf("IP addresses for %s:\n\n", "localhost");

	for(p = addr; p != NULL; p = p->ai_next){
		void *addr;
		char *ipver;

		if (p->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;		
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
		printf("  %s: %s | protocol: %d\n", ipver, ipstr, p->ai_protocol);
	}

	s = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if(s == -1){
		perror("Socket:");
		exit(1);
	}

	if(bind(s, addr->ai_addr, addr->ai_addrlen)){
		perror("Bind:");
		exit(1);
	}

	if(listen(s, 20) == -1){
		perror("listen:");
		exit(1);
	}

	while(1){
		struct sockaddr_storage their_addr;
		socklen_t len = sizeof their_addr;
		int newsock = accept(s, (struct sockaddr *) &their_addr, &len); 
		if(newsock == -1){
			perror("Accept:");
			exit(1);
		}

		inet_ntop(their_addr.ss_family, 
			(their_addr.ss_family == AF_INET ? 
			 	(void *) &(((struct sockaddr_in*)&their_addr)->sin_addr) : 
				(void *) &(((struct sockaddr_in6*)&their_addr)->sin6_addr)),
			ipstr, 
			sizeof(ipstr));

		printf("[Server] accepted new client with address: %s\n", ipstr); 

		send(newsock, ty, strlen(ty), 0);
		close(newsock);
	}

	freeaddrinfo(addr);

	return 0;
}
