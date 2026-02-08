#include "../minishell.h"

#define PATHNAME_SIZE 1024

void	built_in_pwd(t_data *data, t_cmd *cmd)
{
	char	path_name[PATHNAME_SIZE];
	int		saved_stdout;
	int		error_flag;

	saved_stdout = -1;
	error_flag = 0;
	ft_memset(path_name, '\0', PATHNAME_SIZE);
	if (cmd->type != NO_REDIR && save_and_redirects(cmd, &saved_stdout) != 0)
	{
		set_exit_status(data->env, ERROR);
		return ;
	}
	if (getcwd(path_name, PATHNAME_SIZE))
	{
		ft_putstr_fd(path_name, 1);
		write(1, "\n", 1);
	}
	else
	{
		perror("pwd");
		error_flag = 1;
	}
	if (saved_stdout != -1)
		dup2_and_close(saved_stdout, STDOUT_FILENO);
	if (error_flag)
		set_exit_status(data->env, ERROR);
	else
		set_exit_status(data->env, SUCCESS);
}
