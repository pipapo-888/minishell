#include "minishell.h"

built_in_exit(t_data *data, char **argv)
{
	if (argv[1] == NULL)
		exit(0);
	// if (argv[2] != NULL)
}