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

void	ft_execve(t_cmd *cmd, t_data *data, char **env)
{
	pid_t	pid;

	if (built_in_check(cmd, data) == 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		setup_redirects(cmd);
		execve(cmd->path, cmd->argv, env);
		perror("execve");
		exit(1);
	}
	else
		wait(NULL);
}
