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

void if_existing(t_env *existing, char *value, char *key)
{
	free(existing->value);
	existing->value = value;
	existing->type = SHOW;
	free(key);
}

static void	add_new_env(t_data *data, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_export_node(key, value);
	add_env_back(&data->env, new_node);
	free(key);
	if (value)
		free(value);
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

void	built_in_export(t_data *data, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (examine_argv(argv[i]) == 0)
			export_one(data, argv[i]);
		i++;
	}
}
