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
	cmd->path = search_path(cmd->argv[0], ev);
}
