#include "./minishell.h"


int	built_in_check(t_cmd *cmd, t_data *data, char **env)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (built_in_echo(data, cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (built_in_cd(cmd, env, data), 0);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (built_in_pwd(data, cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (built_in_export(data, cmd->argv), 0);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (built_in_unset(data, cmd->argv), 0);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (built_in_env(data, cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		free_exit(data, env, ERROR);
	return (1);
}

static void	check_access_deny(t_data *data, char **env)
{
	struct stat	st;

	if (stat(data->cmd->path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->argv[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else if (access(data->cmd->path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(data->cmd->argv[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
		return ;
	free_exit(data, env, ACCESS_DENY);
}

static void	check_no_command(t_data *data, char *argv, char **env)
{
	if (ft_strchr(argv, '/') != NULL || get_env_value(env, "PATH") == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	free_exit(data, env, NO_COMMAND);
}

void	child_prosess(t_data *data, char **env, int pfd[2], int prev_fd)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (prev_fd != -1)
	{
		if (dup2_and_close(prev_fd, STDIN_FILENO) < 0)
			free_exit(data, env, ERROR);
	}
	if (data->cmd->next != NULL)
	{
		close(pfd[0]);
		if (dup2_and_close(pfd[1], STDOUT_FILENO) < 0)
			free_exit(data, env, ERROR);
	}
	if (setup_redirects(data->cmd) != 0)
		free_exit(data, env, ERROR);
	if (built_in_check(data->cmd, data, env) == 0)
		free_exit(data, env, SUCCESS);
	if (data->cmd->path == NULL)
		check_no_command(data, data->cmd->argv[0], env);
	check_access_deny(data, env);
	execve(data->cmd->path, data->cmd->argv, env);
	perror("minishell: execve:");
	free_exit(data, env, ERROR);
}

static int	update_prev_fd(int pfd[2], int prev_fd, t_cmd *cmd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next != NULL)
	{
		close(pfd[1]);
		return (pfd[0]);
	}
	return (-1);
}

void	set_status_child_process(t_data *data, int status)
{
	if (WIFEXITED(status))
		set_exit_status(data->env, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		set_exit_status(data->env, 128 + WTERMSIG(status));
	}
}

static void	handle_process(t_data *data, t_cmd *cmd, char **env)
{
	int		pfd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (cmd != NULL)
	{
		data->cmd = cmd;
		if (cmd->next != NULL)
			pipe(pfd);
		pid = fork();
		if (pid == 0)
			child_prosess(data, env, pfd, prev_fd);
		prev_fd = update_prev_fd(pfd, prev_fd, cmd);
		cmd = cmd->next;
	}
}

void	ft_execve(t_cmd *cmd, t_data *data, char **env)
{
	int		status;
	t_cmd	*head;

	head = cmd;
	if (cmd->next == NULL && built_in_check(cmd, data, env) == 0)
		return ;
	signal(SIGINT, SIG_IGN);
	handle_process(data, cmd, env);
	data->cmd = head;
	while (wait(&status) > 0)
		;
	set_status_child_process(data, status);
	signal(SIGINT, handler);
}
