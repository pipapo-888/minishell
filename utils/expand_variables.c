#include "../minishell.h"

int	is_valid_variable_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

char	*expand_variables(char *str, t_env *env)
{
	char	*result;
	char	*temp;
	int		i;

	temp = str;
	i = 1;
	while (temp[i] != '\0')
	{
		if (is_valid_variable_char(temp[i]) == 0)
			break ;
		i++;
	}
	char c = temp[i];
	if (i == 0)
		return (ft_strdup(""));
	str = ft_substr(temp, 1, i - 1);
	result = NULL;
	while (env->next != NULL)
	{
		if (ft_strcmp(str, env->key) == 0)
		{
			result = ft_strdup(env->value);
			result = ft_strjoin(result, &c);
			free(str);
			return (result);
		}
		env = env->next;
	}
	return (NULL);
}
