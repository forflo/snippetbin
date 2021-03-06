#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv){
	int status;
	struct addrinfo *addr, *p;
	struct addrinfo hint;
	char ipstr[INET6_ADDRSTRLEN];

	if (argc != 2){
		fprintf(stderr, "usage: showip <hostname>\n");
		exit(1);
	}

	memset(&hint, 0, sizeof (struct addrinfo));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	
	if(status = getaddrinfo(argv[1], "http", &hint, &addr)){
		fprintf(stderr, "[Error]%s\n", gai_strerror(status));
		exit(1);
	}

	printf("IP addresses for %s:\n\n", argv[1]);

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
		printf("  %s: %s\n", ipver, ipstr);
	}

	freeaddrinfo(addr);

	return 0;
}
