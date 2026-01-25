#include "./minishell.h"

int	built_in_check(t_cmd *cmd, t_data *data)
{
	char	**env;

	env = NULL;
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (built_in_echo(cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "cd"))
	{
		env = env_to_array(data->env);
		built_in_cd(cmd, env);
		free_split(env);
		return (0);
	}
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

void	child_prosess(t_data *data, t_cmd *cmd, char **env, int pfd[2],
		int prev_fd)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (prev_fd != -1)
		dup2_and_close(prev_fd, STDIN_FILENO);
	if (cmd->next != NULL)
	{
		close(pfd[0]);
		dup2_and_close(pfd[1], STDOUT_FILENO);
	}
	if (setup_redirects(cmd) != 0)
		exit(1);
	if (built_in_check(cmd, data) == 0)
		exit(0);
	execve(cmd->path, cmd->argv, env);
	perror("execve");
	exit(1);
}

void	ft_execve(t_cmd *cmd, t_data *data, char **env)
{
	int		pfd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	if (cmd->next == NULL && built_in_check(cmd, data) == 0)
		return ;
	while (cmd != NULL)
	{
		if (cmd->next != NULL)
			pipe(pfd);
		pid = fork();
		if (pid == 0)
			child_prosess(data, cmd, env, pfd, prev_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next != NULL)
		{
			close(pfd[1]);
			prev_fd = pfd[0];
		}
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
}
