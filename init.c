#include "./minishell.h"

int	built_in_check(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (chdir(cmd->argv[1]), 0);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		exit(1);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (printf("echo実装前\n"), 0);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (printf("export実装前\n"), 0);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (printf("unset実装前\n"), 0);
	return (1);
}

void	cmd_init(t_cmd *cmd, char *input, char **ev)
{
	char	**argv;
	char	**filtered_argv;

	argv = space_tab_split(input);
	if (argv == NULL)
	{
		cmd->argv = NULL;
		cmd->path = NULL;
		cmd->next = NULL;
		return ;
	}
	parse_redirects(cmd, argv);
	filtered_argv = filter_redirects(argv);
	free_split(argv);
	if (filtered_argv == NULL || filtered_argv[0] == NULL)
	{
		if (filtered_argv)
			free(filtered_argv);
		cmd->argv = NULL;
		cmd->path = NULL;
		cmd->next = NULL;
		return ;
	}
	cmd->argv = filtered_argv;
	cmd->next = NULL;
	printf("cmd->argv[0]: %s\n", cmd->argv[0]);
	printf("cmd->argv[1]: %s\n", cmd->argv[1]);
	printf("cmd->infile: %s\n", cmd->infile);
	printf("cmd->outfile: %s\n", cmd->outfile);
	cmd->path = search_path(cmd->argv[0], ev);
}
