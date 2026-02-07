#include "../minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

void	built_in_echo(t_data *data, t_cmd *cmd)
{
	int	i;
	int	n_flag;
	int	saved_stdout;

	saved_stdout = -1;
	if (cmd->type != NO_REDIR && save_and_redirects(cmd, &saved_stdout) != 0)
		return(set_exit_status(data->env, ERROR), NULL);
	i = 1;
	while (cmd->argv[i] && is_n_flag(cmd->argv[i]))
		i++;
	n_flag = i > 1;
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i++], 1);
		if (cmd->argv[i])
			write(1, " ", 1);
	}
	if (!n_flag)
		write(1, "\n", 1);
	if (saved_stdout != -1)
	{
		if (dup2_and_close(saved_stdout, STDOUT_FILENO) < 0)
			return ;
	}
	set_exit_status(data->env, SUCCESS);
}
