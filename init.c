#include "./minishell.h"

#define PATHNAME_SIZE 1024

void	built_in_pwd(t_cmd *cmd)
{
	char	pathName[PATHNAME_SIZE];
	int		saved_stdout;

	// char	*res;
	// res = getcwd(pathName, PATHNAME_SIZE);
	// printf("res; %s\n", res);
	// printf("pathname; %s\n", pathName);
	ft_memset(pathName, '\0', PATHNAME_SIZE);
	if (cmd->type == NO_REDIR)
	{
		if (getcwd(pathName, PATHNAME_SIZE))
			printf("%s\n", pathName);
		else
			perror("pwd");
	}
	else
	{
		saved_stdout = dup(STDOUT_FILENO);
		setup_redirects(cmd);
		if (getcwd(pathName, PATHNAME_SIZE))
			printf("%s\n", pathName);
		else
			perror("pwd");
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	return ;
}

void	built_in_env(char **ev)
{
	int	i;

	i = 0;
	printf("自作env\n");
	while (ev[i] != NULL)
	{
		printf("%s\n", ev[i]);
		i++;
	}
	return ;
}

int	built_in_check(t_cmd *cmd, char **ev)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (printf("echo実装前\n"), 0);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (chdir(cmd->argv[1]), 0);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (built_in_pwd(cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (printf("export実装前\n"), 0);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (printf("unset実装前\n"), 0);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (built_in_env(ev), 0);
	// if (!ft_strcmp(cmd->argv[0], "exit"))
	// 	exit(1);
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
