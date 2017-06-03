#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "world.h"
#include "world_toroidal.h"
#include "world_limited.h"
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
	
	if (!strcmp(config.type, "toroidal")) {
		struct world_toroidal *wt = world_toroidal_alloc(&config);
		if (!wt) {
			perror("Can't allocate world");
			return EXIT_FAILURE;
		}
	
		w = (struct world *)wt;
	
		do {
			printf("\033cIteration %d\n", i++);
			world_print(w);
			world_iterate(w);
		} while (getchar() != 'q');
	
		world_toroidal_free(wt);
	} else if (!strcmp(config.type, "limited")) {
		struct world_limited *wl = world_limited_alloc(&config);
		if (!wl) {
			perror("Can't allocate world");
			return EXIT_FAILURE;
		}
	
		w = (struct world *)wl;
	
		do {
			printf("\033cIteration %d\n", i++);
			world_print(w);
			world_iterate(w);
		} while (getchar() != 'q');
	
		world_limited_free(wl);
	} else {
		printf("\nType of the world is not correct.\n");
		return EXIT_FAILURE;
	}
		

	return EXIT_SUCCESS;
}