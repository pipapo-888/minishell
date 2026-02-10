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

t_env *copy_env_list(t_env *env)
{
	t_env *new;
	t_env *last;
	t_env *node;

	new = NULL;
	last = NULL;
	while(env)
	{
		if (env->type == SHOW && env->value && strcmp(env->key, "_"))
		{
			node = malloc(sizeof(t_env));
			if (!node)
				return (NULL);
			node->key = ft_strdup(env->key);
			node->value = ft_strdup(env->value);
			node->type = env->type;
			node->next = NULL;
			if (!new)
				new =  node;
			else
				env_add_back(&new, node);
		}
		env = env->next;
	}
	return (new);
}

void env_swap(t_env *a, t_env *b)
{
    char *tmp_key;
    char *tmp_val;
	t_export_type temp_type;

	temp_type = a->type;
    tmp_key = a->key;
    tmp_val = a->value;
	a->type = b->type;
    a->key = b->key;
    a->value = b->value;
	b->type = temp_type;
    b->key = tmp_key;
    b->value = tmp_val;
}


void sort_env_list(t_env *env)
{
	t_env *i;
    t_env *j;

    i = env;
    while (i)
    {
        j = i->next;
        while (j)
        {
            if (ft_strcmp(i->key, j->key) > 0)
                env_swap(i, j);
            j = j->next;
        }
        i = i->next;
    }
}

void print_export(t_data *data, t_env *env)
{
	char	**arr;
	int		i;
	int		saved_stdout;

	saved_stdout = -1;
	if (data->cmd->type != NO_REDIR && save_and_redirects(data->cmd, &saved_stdout) != 0)
	{
		set_exit_status(data->env, ERROR);
		return ;
	}
	set_exit_status(data->env, SUCCESS);
	arr = env_to_array(env, SHOW);
	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(arr[i], 1);
		write(1, "\n", 1);
		i++;
	}
	free_split(arr);
	if (saved_stdout != -1)
		dup2_and_close(saved_stdout, STDOUT_FILENO);
}

void declare_x(t_data *data, t_env *env)
{
	(void)data;

	t_env *copy;

	copy = copy_env_list(env);
	sort_env_list(copy);
	print_export(data, copy);
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
