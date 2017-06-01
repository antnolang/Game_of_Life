#include <stdio.h>
#include <stdlib.h>
#include "gol.h"
#include "config.h"

int main(int argc, char *argv[])
{
	int i = 0;
	struct world *w;
	struct config config;
	
	if (!config_parse_argv(&config, argc, argv)) {
		printf("\nERROR: configuration is not valid.\n\n");
		config_print_usage(argv[0]);
		return EXIT_FAILURE;
	} else if (config.show_help) {
		config_print_usage(argv[0]);
		return EXIT_SUCCESS;
	}
	
	w = world_alloc(&config);
	if (!w) {
		perror("Can't allocate world");
		return EXIT_FAILURE;
	}
		
	do {
		printf("\033cIteration %d\n", i++);
		world_print(w);
		world_iterate(w);
	} while (getchar() != 'q');
	
	world_free(w);

	return EXIT_SUCCESS;
}