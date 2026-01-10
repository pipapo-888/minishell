#include "./minishell.h"

int	built_in_check(t_cmd *cmd, t_data *data, char **ev)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (built_in_echo(cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (built_in_cd(cmd, ev), 0);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (built_in_pwd(cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (built_in_export(data, cmd->argv), 0);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (built_in_unset(data, cmd->argv), 0);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (built_in_env(data->env), 0);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		exit(1);
	return (1);
}

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
