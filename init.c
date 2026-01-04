#include "./minishell.h"

#define PATHNAME_SIZE 1024

void	built_in_pwd(t_cmd *cmd)
{
	char	pathName[PATHNAME_SIZE];
	int		saved_stdout;

	// char	*res;
	// res = getcwd(pathName, PATHNAME_SIZE);
	// printf("res; %s\n", res);
	// printf("pathname; %s\n", pathName);
	ft_memset(pathName, '\0', PATHNAME_SIZE);
	if (cmd->type == NO_REDIR)
	{
		if (getcwd(pathName, PATHNAME_SIZE))
			printf("%s\n", pathName);
		else
			perror("pwd");
	}
	else
	{
		saved_stdout = dup(STDOUT_FILENO);
		setup_redirects(cmd);
		if (getcwd(pathName, PATHNAME_SIZE))
			printf("%s\n", pathName);
		else
			perror("pwd");
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	return ;
}

void	built_in_env(char **ev)
{
	int	i;

	i = 0;
	printf("自作env\n");
	while (ev[i] != NULL)
	{
		printf("%s\n", ev[i]);
		i++;
	}
	return ;
}

int	built_in_check(t_cmd *cmd, char **ev)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (printf("echo実装前\n"), 0);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (chdir(cmd->argv[1]), 0);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (built_in_pwd(cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (printf("export実装前\n"), 0);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (printf("unset実装前\n"), 0);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (built_in_env(ev), 0);
	// if (!ft_strcmp(cmd->argv[0], "exit"))
	// 	exit(1);
	return (1);
}

int	skip_spaces(const char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]) == 1)
		i++;
	return (i);
}

t_token	*extract_quoted_token(const char *input, int *len)
{
	t_token	*token;
	int		end_quote;
	char	c;

	end_quote = 1;
	c = input[0];
	while (input[end_quote] != '\0' && input[end_quote] != c)
		end_quote++;
	if (input[end_quote] != c)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = WORD;
	token->value = ft_substr(input, 1, end_quote - 1);
	token->next = NULL;
	*len = end_quote + 1;
	return (token);
}

t_token	*extract_pipe_token(const char *input, int *len)
{
	t_token	*token;

	if (input[0] != '|')
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = PIPE;
	token->value = ft_substr(input, 0, 1);
	token->next = NULL;
	*len = 1;
	return (token);
}

t_token	*extract_redirect_token(const char *input, int *len)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	if (input[0] == '<')
	{
		if (input[1] == '<')
		{
			token->type = HEREDOC;
			token->value = ft_substr(input, 0, 2);
			*len = 2;
		}
		else
		{
			token->type = REDIR_IN;
			token->value = ft_substr(input, 0, 1);
			*len = 1;
		}
	}
	else if (input[0] == '>')
	{
		if (input[1] == '>')
		{
			token->type = REDIR_APPEND;
			token->value = ft_substr(input, 0, 2);
			*len = 2;
		}
		else
		{
			token->type = REDIR_OUT;
			token->value = ft_substr(input, 0, 1);
			*len = 1;
		}
	}
	else
	{
		free(token);
		return (NULL);
	}
	return (token);
}

t_token	*extract_word_token(const char *input, int *len)
{
	t_token	*token;
	int		end;

	end = 0;
	while (input[end] != '\0' && ft_isspace(input[end]) == 0
		&& input[end] != '|' && input[end] != '<' && input[end] != '>')
		end++;
	if (end == 0)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = WORD;
	token->value = ft_substr(input, 0, end);
	token->next = NULL;
	*len = end;
	return (token);
}

static t_token	*tokenize(const char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	int		i;
	int		len;

	head = NULL;
	current = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		i += skip_spaces(&input[i]);
		if (input[i] == '\0')
			break ;
		len = 0;
		if (input[i] == '"' || input[i] == '\'')
			new_token = extract_quoted_token(&input[i], &len);
		else if (input[i] == '|')
			new_token = extract_pipe_token(&input[i], &len);
		else if (input[i] == '<' || input[i] == '>')
			new_token = extract_redirect_token(&input[i], &len);
		else
			new_token = extract_word_token(&input[i], &len);
		if (new_token == NULL)
			break ;
		if (head == NULL)
			head = new_token;
		else
			current->next = new_token;
		current = new_token;
		i += len;
	}
	return (head);
}

static void	setup_word(t_cmd *cmd, t_token *tokens)
{
	int		count;
	int		i;
	char	**argv;

	if (cmd == NULL || tokens == NULL || tokens->type != WORD)
		return ;
	while (tokens != NULL || tokens->type != WORD)
	{
		count++;
		tokens = tokens->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (argv == NULL)
		return ;
	i = 0;
	while (tokens != NULL && tokens->type == WORD)
	{
		argv[i] = ft_strdup(tokens->value);
		if (argv[i] == NULL)
		{
			free_split(argv);
			return ;
		}
		i++;
		tokens = tokens->next;
	}
	argv[i] = NULL;
	cmd->argv = argv;
}

static void	command_setup(t_cmd *cmd, t_token *tokens)
{
	char	**temp;
	size_t	count;

	if (cmd == NULL || tokens == NULL || tokens->type != REDIR_IN
		&& tokens->type != REDIR_OUT && tokens->type != REDIR_APPEND)
		return ;
	while (tokens != NULL)
	{
		if (tokens->type == REDIR_IN)
		{
			tokens = tokens->next;
			if (tokens != NULL && tokens->type == WORD)
			{
				cmd->infile = ft_strdup(tokens->value);
				tokens = tokens->next;
			}
		}
		else if (tokens->type == REDIR_OUT || tokens->type == REDIR_APPEND)
		{
			tokens = tokens->next;
			if (tokens != NULL && tokens->type == WORD)
			{
				cmd->outfile = ft_strdup(tokens->value);
				tokens = tokens->next;
			}
		}
		else
			tokens = tokens->next;
	}
}

void	cmd_init(t_cmd *cmd, char *input, char **ev)
{
	t_token	*tokens;

	tokens = tokenize(input);
	if (tokens == NULL)
		return ;
	while (tokens != NULL)
	{
		setup_word(cmd, tokens);
		command_setup(cmd, tokens);
		tokens = tokens->next;
	}

	// メモリ解放(後で free_tokens 関数として分離)
	while (tokens != NULL)
	{
		t_token *next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}
