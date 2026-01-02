#include "./minishell.h"

static int	handle_redirects(char *argv)
{
	if (ft_strcmp(argv, "<") == 0)
		return (0);
	else if (ft_strcmp(argv, ">") == 0)
		return (0);
	else if (ft_strcmp(argv, ">>") == 0)
		return (0);
	return (1);
}

static int	count_args(char **argv)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (argv[i] != NULL)
	{
		if (handle_redirects(argv[i]) == 0)
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**filter_redirects(char **argv)
{
	char	**new_argv;
	int		i;
	int		j;
	int		count;

	if (argv == NULL)
		return (NULL);
	count = count_args(argv);
	new_argv = malloc(sizeof(char *) * (count + 1));
	if (new_argv == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (argv[i] != NULL)
	{
		if (handle_redirects(argv[i]) == 0)
			i += 2;
		else
			new_argv[j++] = ft_strdup(argv[i++]);
	}
	new_argv[j] = NULL;
	return (new_argv);
}
