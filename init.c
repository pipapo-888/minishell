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

static char	**piped_split(const char *str)
{
	char	**result;

	result = ft_split(str, '|');
	if (result == NULL)
		return (NULL);
	return (result);
}

static void	command_setup(t_cmd *cmd, char *argv, char **env)
{
	char	**filtered_argv;
	char	**temp;

	if (cmd == NULL || argv == NULL || env == NULL)
		return ;
	temp = space_tab_split(argv);
	if (temp == NULL)
		return ;
	parse_redirects(cmd, temp);
	filtered_argv = filter_redirects(temp);
	cmd->argv = filtered_argv;
	cmd->path = search_path(cmd->argv[0], env);
	free_split(temp);
}

void	cmd_init(t_cmd *cmd, char *input, char **ev)
{
	char	**piped_argv;
	int		i;

	piped_argv = piped_split(input);
	i = 0;
	while (piped_argv != NULL && piped_argv[i] != NULL)
	{
		command_setup(cmd, piped_argv[i], ev);
		cmd->next = NULL;
		i++;
	}
	free_split(piped_argv);
}
