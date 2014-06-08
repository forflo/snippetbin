#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static int verbose_flag;

int main(int argc, char **argv){
	int c;
	char *optstring = "t:f:s";
	char *type;
	char *flags;
	int read_stdin = 0;
	
	while(1){
		static struct option long_options[] = {
			{"type", required_argument, NULL, 't'},
			{"flags", required_argument, NULL, 'f'},
			{"stdin", no_argument, NULL, 's'},
			{0, 0, 0, 0}
		};

		int option_index = 0;
		c = getopt_long(argc, argv, optstring, long_options, &option_index);
		
		if(c == -1){
			break;
		} 
		switch (c){
			case 't':
				type = optarg;
			break;
			case 'f':
				flags = optarg;
			break;
			case 's':
				read_stdin = 1;
			break;
			case '?':
			break;
			default:
				printf("Error beim Parsen der Argumente!\n");
				exit(1);
			break;
			
		}
	}

	printf("type: %s, flags: %s, read_stdin: %d\n", type, flags, read_stdin);

	if(optind < argc){
		printf("Es gibt weitere ARGV-Elemente: ");
		while(optind < argc){
			printf("%s", argv[optind++]);
		}
		printf("\n");
	}
return EXIT_SUCCESS;
	
}
