#include "../minishell.h"

static char	*ft_strjoin_char(char *str, char c)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, len + 1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

int	is_valid_variable_char(char c, int first)
{
	if (first)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
			return (1);
		return (0);
	}
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

static char	*get_env_var(char *key, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

static int	get_var_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_valid_variable_char(str[i], i == 0))
		i++;
	return (i);
}

static char	*expand_single_var(char *str, int *i, t_env *env)
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
	var_len = get_var_len(&str[*i]);
	if (var_len == 0)
		return (ft_strdup(""));
	key = ft_substr(str, *i, var_len);
	value = get_env_var(key, env);
	free(key);
	*i += var_len - 1;
	return (value);
}

char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	char	*temp;
	char	*expanded;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			expanded = expand_single_var(str, &i, env);
			temp = result;
			result = ft_strjoin(result, expanded);
			free(temp);
			free(expanded);
		}
		else
		{
			temp = result;
			result = ft_strjoin_char(result, str[i]);
			free(temp);
		}
		i++;
	}
	return (result);
}

