#include "../minishell.h"

int	argument_count(char **argv)
{
	int	count;

	count = 0;
	while (argv[count] != NULL)
		count++;
	return (count);
}

void	built_in_cd(t_cmd *cmd, char **ev)
{
	char	*path;

	if (argument_count(cmd->argv) > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return ;
	}
	path = NULL;
	if (cmd->argv[1] == NULL || ft_strcmp(cmd->argv[1], "~") == 0)
	{
		path = get_env_value(ev, "HOME");
		if (path == NULL)
			return (perror("cd: HOME not set"));
	}
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		path = get_env_value(ev, "OLDPWD");
		if (path == NULL)
			return (perror("cd: OLDPWD not set"));
	}
	if (path != NULL)
	{
		if (chdir(path) != 0)
			return (perror("cd"));
		return ;
	}
	if (chdir(cmd->argv[1]) != 0)
		return (perror("cd"));
}
