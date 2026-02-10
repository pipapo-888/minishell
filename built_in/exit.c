#include "../minishell.h"
#define numeric 2
#define too_many 1

void	put_error_exit(t_data *data, t_cmd *cmd, char **env, int type)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->argv[1], 2);
	if (type == numeric)
	{
		ft_putstr_fd(": numeric argument required\n", 2);
		set_exit_status(data->env, ERROR);
		free_exit(data, env, ERROR);
	}
	else if (type == too_many)
	{
		ft_putstr_fd(": too many arguments\n", 2);
		set_exit_status(data->env, SHELL_ERROR);
		free_exit(data, env, SHELL_ERROR);
	}
}

static int	is_numeric_digit(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[i] == '\0')
		return (1);
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	too_many_arguments(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd->argv[count] != NULL)
		count++;
	if (count > 2)
		return (1);
	return (0);
}

void	built_in_exit(t_data *data, t_cmd *cmd, char **env)
{
	long long	code;

	ft_putstr_fd("exit\n", 2);
	if (cmd->argv[1] == NULL)
		free_exit(data, env, SUCCESS);
	if (is_numeric_digit(cmd->argv[1]) != 0
		|| llong_check_atoi(cmd->argv[1]) != 0)
		put_error_exit(data, cmd, env, numeric);
	if (too_many_arguments(cmd) != 0)
		put_error_exit(data, cmd, env, too_many);
	code = ft_atoll(cmd->argv[1]);
	set_exit_status(data->env, (int)(code & 255));
	free_exit(data, env, (int)(code & 255));
}
