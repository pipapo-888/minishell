#include "../minishell.h"

int	argument_count(char **argv)
{
	int	count;

	count = 0;
	while (argv[count] != NULL)
		count++;
	return (count);
}

static void	update_oldpwd(t_data *data, char *old_path)
{
	t_env	*oldpwd;

	oldpwd = find_key(data->env, "OLDPWD");
	if (oldpwd)
	{
		if (oldpwd->value)
			free(oldpwd->value);
		oldpwd->value = ft_strdup(old_path);
	}
}

void	built_in_cd(t_cmd *cmd, char **ev, t_data *data)
{
	char	*path;
	char	old_path[4096];

	if (argument_count(cmd->argv) > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return ;
	}
	if (getcwd(old_path, sizeof(old_path)) == NULL)
		old_path[0] = '\0';
	path = cmd->argv[1];
	if (path == NULL || ft_strcmp(path, "~") == 0)
		path = get_env_value(ev, "HOME");
	else if (ft_strcmp(path, "-") == 0)
		path = get_env_value(ev, "OLDPWD");
	if (!path && (cmd->argv[1] == NULL || ft_strcmp(cmd->argv[1], "~") == 0))
		return (perror("cd: HOME not set"));
	if (!path)
		return (perror("cd: OLDPWD not set"));
	if (chdir(path) != 0)
		return (perror("cd"));
	if (old_path[0] != '\0')
		update_oldpwd(data, old_path);
}
