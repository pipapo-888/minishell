#include "./minishell.h"

void	free_split(char **sp)
{
	int	i;

	if (sp == NULL)
		return ;
	i = 0;
	while (sp[i] != NULL)
	{
		free(sp[i]);
		i++;
	}
	free(sp);
}
