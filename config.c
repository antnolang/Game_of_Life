#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>


static const char *init_mode_str[] = {
	[CFG_DEFAULT] = "default",
	[CFG_GLIDER]  = "glider",
	[CFG_RANDOM]  = "random",
};

static const struct option long_options[] =
{
	{"help",   no_argument,       0, 'h'},
	{"size_x", required_argument, 0, 'x'},
	{"size_y", required_argument, 0, 'y'},
	{"init",   required_argument, 0, 'i'},
	{0, 0, 0, 0}
};

static bool check_config(const struct config *config);
static enum cfg_init_mode str2init_mode(const char *opt);

int config_parse_argv(struct config *config, int argc, char *argv[])
{
	int option_index = 0;
	int c;
	bool check_flags = true;
	
	// Default values
	config->show_help = false;
	config->size_x = 10;
	config->size_y = 10;
	config->init_mode = CFG_DEFAULT;

	while ((c = getopt_long(argc, argv, "hx:y:i:", long_options,
				&option_index)) != -1) {
		switch (c) {
		case 'h':
			config->show_help = true;
			break;
		case 'x':
			config->size_x = strtol(optarg, NULL, 0);
			break;
		case 'y':
			config->size_y = strtol(optarg, NULL, 0);
			break;
		case 'i':
			config->init_mode = str2init_mode(optarg);
			break;
		case '?':
			check_flags = false;
			break;
		default:
			printf("\nERROR\n");
			exit(EXIT_FAILURE);
 		}
	}
	
	int i;
	for (i = optind; i < argc; i++)
		printf("Argumento desconocido: \"%s\"\n", argv[i]);

	return check_flags && check_config(config);
}

static bool check_config(const struct config *config)
{
	bool correct = true;

	if (config->show_help)
		return true;

	correct &= config->size_x > 0;
	correct &= config->size_y > 0;
	correct &= config->init_mode != CFG_NOT_DEF;

	return correct;
}

static enum cfg_init_mode str2init_mode(const char *opt)
{
	int i;
	for (i = 0; i < CFG_N_INIT_MODES; i++)
		if (!strcmp(init_mode_str[i], opt))
			break;

	return i == CFG_N_INIT_MODES ? CFG_NOT_DEF : i;
}

void config_print_usage(const char *arg0)
{
	printf("Usage: %s\n"
		"\t[-h|--help]\n"
		"\t[-x|--size_x <num>]\n"
		"\t[-y|--size_y <num>]\n"
		"\t[-i|--init <init_mode>]\n"
		, arg0);

	printf("\ninitialization modes: \n");
	
	int i;
	for (i = 0; i < CFG_N_INIT_MODES; i++)
		printf("- %s\n", init_mode_str[i]);
}

void config_print(const struct config *config)
{
	printf("config {\n");
	printf("\tshow help = %s\n", config->show_help ? "TRUE" : "FALSE");
	printf("\tsize_x    = %d\n", config->size_x);
	printf("\tsize_y    = %d\n", config->size_y);
	printf("\tinit_mode = %d(%s)\n",
		config->init_mode, init_mode_str[config->init_mode]);
	printf("}\n");
}
