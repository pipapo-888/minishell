#include "minishell.h"

static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		env = env->next;
		count++;
	}
	return (count);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	char	*tmp;
	int		size;
	int		i;

	size = env_list_size(env);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->type == DONT_SHOW || env->value == NULL)
		{
			env = env->next;
			continue ;
		}
		if (env->value)
		{
			tmp = ft_strjoin(env->key, "=");
			arr[i] = ft_strjoin(tmp, env->value);
			free(tmp);
		}
		else
			arr[i] = ft_strdup(env->key);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static t_env	*create_env_node(char *envp_line)
{
	t_env	*node;
	char	*equal_pos;
	int		key_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_pos = ft_strchr(envp_line, '=');
	if (equal_pos)
	{
		key_len = equal_pos - envp_line;
		node->key = ft_substr(envp_line, 0, key_len);
		node->value = ft_strdup(equal_pos + 1);
		node->type = SHOW;
	}
	else
	{
		node->key = ft_strdup(envp_line);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

static void	env_add_back(t_env **head, t_env *new_node)
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

void	env_init(t_data *data, char **envp)
{
	t_env	*new_node;
	int		i;

	i = 0;
	data->env = NULL;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (new_node)
			env_add_back(&data->env, new_node);
		i++;
	}
	env_add_back(&data->env, create_env_node("?"));
	// env_add_back(&data->env, create_env_node("PATH=asdfklasjfl/"));

}
