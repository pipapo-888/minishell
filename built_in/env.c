#include "../minishell.h"

void	built_in_env(t_env *env)
{
	char	**arr;
	int		i;

	arr = env_to_array(env, SHOW);
	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		ft_putstr_fd(arr[i], 1);
		write(1, "\n", 1);
		i++;
	}
	free_split(arr);
}
