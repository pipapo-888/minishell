#include "../minishell.h"

static t_env	*find_key(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static t_env	*create_export_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->type = SHOW;
	node->next = NULL;
	return (node);
}

static void	add_env_back(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

static void	export_one(t_data *data, char *arg)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	t_env	*existing;
	t_env	*new_node;

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
	{
		free(existing->value);
		existing->value = value;
		existing->type = SHOW;
		free(key);
	}
	else
	{
		new_node = create_export_node(key, value);
		add_env_back(&data->env, new_node);
		free(key);
		if (value)
			free(value);
	}
}

void	built_in_export(t_data *data, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		export_one(data, argv[i]);
		i++;
	}
}
