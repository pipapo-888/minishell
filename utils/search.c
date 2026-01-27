#include "../minishell.h"

char	*get_env_value(char *const envp[], const char *key)
{
	size_t	klen;
	int		i;

	if (envp == NULL || key == NULL)
		return (NULL);
	i = 0;
	klen = ft_strlen(key);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, klen) == 0)
			return (&envp[i][klen + 1]);
		i++;
	}
	return (NULL);
}

static char	*try_join_exec(const char *dir, const char *bin)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (tmp == NULL)
		return (NULL);
	full = ft_strjoin(tmp, bin);
	free(tmp);
	return (full);
}

char	*search_path(const char *cmd, char *const envp[])
{
	char	*path;
	char	**dirs;
	char	*full;
	int		i;

	if (cmd == NULL)
		return (NULL);
	path = get_env_value(envp, "PATH");
	if (path == NULL)
		return (NULL);
	dirs = ft_split(path, ':');
	if (dirs == NULL)
		return (NULL);
	i = 0;
	while (dirs[i] != NULL)
	{
		full = try_join_exec(dirs[i], cmd);
		if (full == NULL)
			return (free_split(dirs), NULL);
		if (access(full, X_OK) == 0)
			return (free_split(dirs), full);
		free(full);
		i++;
	}
	return (free_split(dirs), NULL);
}
