#include "./minishell.h"

static int	quote_unclosed(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			i++;
			while (input[i] != '\0' && input[i] != quote)
				i++;
			if (input[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

char	*free_strjoin(char *str1, char *str2)
{
	char	*new_line;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	new_line = ft_strjoin(str1, str2);
	free(str1);
	return (new_line);
}

void	ft_wait_input(t_data *data)
{
	char	*next_line;

	if (data->input == NULL)
		return ;
	while (quote_unclosed(data->input) != 0)
	{
		data->input = free_strjoin(data->input, "\n");
		next_line = readline("> ");
		if (next_line == NULL)
			break ;
		data->input = free_strjoin(data->input, next_line);
		free(next_line);
	}
}

static int	is_empty_input(char *input)
{
	int	i;

	if (input == NULL || input[0] == '\0')
		return (1);
	i = 0;
	while (input[i] != '\0')
	{
		if (ft_isspace(input[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	prompt(t_data data)
{
	char	**env;

	data.input = readline("minishell$ ");
	ft_wait_input(&data);
	if (data.input == NULL)
		exit(1);
	if (is_empty_input(data.input) != 0)
	{
		free(data.input);
		return ;
	}
	add_history(data.input);
	env = env_to_array(data.env, EXPAND);
	cmd_init(&data);
	cmd_setup(&data, data.cmd, data.input, env);
	if (data.cmd->argv == NULL)
	{
		free_all(&data);
		free_split(env);
		return ;
	}
	ft_execve(data.cmd, &data, env);
	free_all(&data);
	free_split(env);
}
