#include "../minishell.h"

t_env *copy_env_list(t_env *env)
{
	t_env *new;
	t_env *node;

	new = NULL;
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
	// ここにfree_env_listを追加してcopyおfreeする！
	return ;
}