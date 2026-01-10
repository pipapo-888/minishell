#include "./minishell.h"
#include <signal.h>

void	ft_execve(t_cmd *cmd, t_data *data, char **ev)
{
	pid_t	pid;

	// printf("PATH: %s\n", cmd->path);
	// printf("ARGV[0]: %s\n", cmd->argv[0]);
	// printf("ARGV[1]: %s\n", cmd->argv[1]);
	if (built_in_check(cmd, data, ev) == 0)
		return ;
	pid = fork();
	// printf("%d\n", pid);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		setup_redirects(cmd);
		execve(cmd->path, cmd->argv, ev);
		perror("execve");
		exit(1);
	}
	else
	{
		wait(NULL);
	}
}

void	prompt(char **ev, t_data data)
{
	data.cmd = malloc(sizeof(t_cmd));
	if (data.cmd == NULL)
		return ;
	data.cmd->argv = NULL;
	data.cmd->path = NULL;
	data.cmd->infile = NULL;
	data.cmd->outfile = NULL;
	data.cmd->type = NO_REDIR;
	data.cmd->next = NULL;
	data.input = readline("minishell$ ");
	if (data.input == NULL || data.input[0] == '\0')
	{
		free(data.input);
		free(data.cmd);
		if (data.input == NULL)
			exit(1);
		return ;
	}
	add_history(data.input);
	cmd_init(data.cmd, data.input, ev);
	if (data.cmd->argv == NULL)
	{
		free(data.input);
		free(data.cmd);
		return ;
	}
	ft_execve(data.cmd, &data, ev);
	free_split(data.cmd->argv);
	free(data.cmd->path);
	free(data.cmd);
	free(data.input);
}

void	handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	char	*program_name;
	t_data	data;

	env_init(&data, envp);

	(void)ac;
	(void)av;
	(void)program_name;
	data.cmd = NULL;
	data.input = NULL;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt(envp, data);
	}
	// exit(1);
	return (0);
}
