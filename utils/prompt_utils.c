#include "../minishell.h"

int	quote_unclosed(char *input)
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

int	is_empty_input(char *input)
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
