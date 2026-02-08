#include "../minishell.h"

void	if_existing(t_env *existing, char *value, char *key)
{
	if (existing->value && strcmp(key, "OLDPWD") != 0)
		free(existing->value);
	if (strcmp(key, "OLDPWD") != 0 && value == NULL)
		existing->value = value;
	existing->type = SHOW;
	free(key);
}

static void	export_one(t_data *data, char *arg)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	t_env	*existing;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		key = ft_substr(arg, 0, equal_pos - arg);
		value = ft_strdup(equal_pos + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	existing = find_key(data->env, key);
	if (existing)
		if_existing(existing, value, key);
	else
		add_new_env(data, key, value);
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	examine_argv(char *str)
{
	if (!is_valid_identifier(str))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

void declare_x(t_data *data, t_env *env)
{
	(void)data;
	// t_env *head = env;


	t_env *copy = malloc(sizeof(t_env));
	if (copy == NULL)
		return ;




	int len = env_list_size(env);

	printf("%d", len);


	// a->z
	// env to array で表示
	// index 通りの順番にもどす
	return ;
}

void	built_in_export(t_data *data, char **argv)
{
	int	i;
	int	error_flag;

	i = 1;
	error_flag = 0;
	if (argv[1] == NULL)
		declare_x(data, data->env);
		
	while (argv[i])
	{
		if (examine_argv(argv[i]) == 0)
			export_one(data, argv[i]);
		else 
			error_flag = 1;
		i++;
	}
	if (error_flag == 0)
		set_exit_status(data->env, SUCCESS);
	else
		set_exit_status(data->env, ERROR);
}
