#include "../minishell.h"

void	set_exit_status(t_env *env, int status)
{
	t_env	*node;
	char	*new_value;

	node = find_key(env, "?");
	if (!node)
		return ;
	new_value = ft_itoa(status);
	if (!new_value)
		return ;
	free(node->value);
	node->value = new_value;
}
