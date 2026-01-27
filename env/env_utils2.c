#include "../minishell.h"

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

void	add_new_env(t_data *data, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_export_node(key, value);
	env_add_back(&data->env, new_node);
	free(key);
	if (value)
		free(value);
}
