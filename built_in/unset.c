#include "../minishell.h"

void	built_in_unset(t_data *data, char **argv)
{
	int		i;
	t_env	*current;

	i = 1;
	while (argv[i])
	{
		current = data->env;
		while (current)
		{
			if (ft_strcmp(current->key, argv[i]) == 0)
			{
				current->type = DONT_SHOW;
				free(current->value);
				current->value = NULL;
				break ;
			}
			current = current->next;
		}
		i++;
	}
}
