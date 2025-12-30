#include "./minishell.h"

void	ft_execve(t_cmd *cmd, char **ev)
{
	pid_t	pid;

	pid = fork();
	printf("%d\n", pid);
	if (pid == 0)
	{
		execve(cmd->path, cmd->argv, ev);
		perror("execve");
		exit(1);
	}
	else
	{
		wait(NULL);
	}
}

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

	argv = space_tab_split(input);
	if (argv == NULL)
	{
		cmd->argv = NULL;
		cmd->path = NULL;
		cmd->next = NULL;
		cmd->type = WORD;
		return ;
	}
	cmd->argv = argv;
	cmd->next = NULL;
	cmd->type = WORD;
	if (built_in_check(cmd) != 0)
		cmd->path = search_path(cmd->argv[0], ev);
	else
		cmd->path = NULL;
}

void	prompt(char **ev)
{
	t_data	data;

	data.cmd = malloc(sizeof(t_cmd));
	if (data.cmd == NULL)
		return ;
	data.input = readline("minishell$ ");
	if (data.input == NULL || data.input[0] == '\0')
	{
		free(data.input);
		free(data.cmd);
		return ;
	}
	cmd_init(data.cmd, data.input, ev);
	if (data.cmd->argv == NULL)
	{
		free(data.input);
		free(data.cmd);
		return ;
	}
	if (built_in_check(data.cmd) != 0)
		ft_execve(data.cmd, ev);
	free_split(data.cmd->argv);
	free(data.cmd->path);
	free(data.cmd);
	free(data.input);
}

int	main(int ac, char **av, char **envp)
{
	char	*program_name;

	// TODO:envpのコピー
	(void)ac;
	(void)av;
	(void)program_name;
	(void)envp;
	while (1)
	{
		prompt(envp);
	}
	// exit(1);
	return (0);
}

// cd exit history echo
