#include "../minishell.h"

static char	*append_expanded(char *result, char *str, int *i, t_env *env)
{
	char	*temp;
	char	*expanded;

	expanded = expand_single_var(str, i, env);
	temp = result;
	result = ft_strjoin(result, expanded);
	free(temp);
	free(expanded);
	return (result);
}

static char	*append_char(char *result, char c)
{
	char	*temp;

	temp = result;
	result = ft_strjoin_char(result, c);
	free(temp);
	return (result);
}

char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			result = append_expanded(result, str, &i, env);
		else
			result = append_char(result, str[i]);
		i++;
	}
	return (result);
}
