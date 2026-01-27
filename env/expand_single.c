#include "../minishell.h"

static char	*get_env_var(char *key, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			if (env->value)
				return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*expand_single_var(char *str, int *i, t_env *env)
{
	char	*key;
	char	*value;
	int		var_len;

	(*i)++;
	if (str[*i] == '\0' || (!is_valid_variable_char(str[*i], 1)
			&& str[*i] != '?'))
	{
		(*i)--;
		return (ft_strdup("$"));
	}
	if (str[*i] == '?')
	{
		return (get_env_var("?", env));
	}
	var_len = get_var_len(&str[*i]);
	if (var_len == 0)
		return (ft_strdup(""));
	key = ft_substr(str, *i, var_len);
	value = get_env_var(key, env);
	free(key);
	*i += var_len - 1;
	return (value);
}
