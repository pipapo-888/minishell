#include "./minishell.h"

#define PATHNAME_SIZE 1024

void	built_in_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;
	int	saved_stdout;

	saved_stdout = -1;
	i = 1;
	n_flag = 0;
	while (cmd->argv[i] && ft_strcmp(cmd->argv[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	if (cmd->type != NO_REDIR)
	{

		printf("aaaa%s", cmd->outfile);
		saved_stdout = dup(STDOUT_FILENO);
		setup_redirects(cmd);
	}
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	return ;
}

void	built_in_pwd(t_cmd *cmd)
{
	char	pathName[PATHNAME_SIZE];
	int		saved_stdout;

	saved_stdout = -1;
	ft_memset(pathName, '\0', PATHNAME_SIZE);
	if (cmd->type != NO_REDIR)
	{
		saved_stdout = dup(STDOUT_FILENO);
		setup_redirects(cmd);
	}
	if (getcwd(pathName, PATHNAME_SIZE))
		printf("%s\n", pathName);
	else
		perror("pwd");
	if (saved_stdout != -1)
	{
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
		return (built_in_echo(cmd), 0);
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

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp != NULL)
	{
		free(temp->value);
		temp = temp->next;
	}
	free(tokens);
}

void	cmd_init(t_cmd *cmd, char *input, char **ev)
{
	t_token	*tokens;
	t_token	*temp;
	t_cmd	*head;

	tokens = tokenize(input);
	if (tokens == NULL)
		return ;
	temp = tokens;
	head = cmd;
	while (temp != NULL)
	{
		if (temp->type == WORD)
		{
			int word_count = 0;
			int i = 0;
			t_token *counter = temp;

			// 連続するWORD数を数える
			while (counter != NULL && counter->type == WORD)
			{
				word_count++;
				counter = counter->next;
			}

			// まとめてmallocする
			cmd->argv = malloc(sizeof(char *) * (word_count + 1));
			if (cmd->argv == NULL)
				return ;

			// WORDを詰めていく
			while (temp != NULL && temp->type == WORD)
			{
				cmd->argv[i++] = ft_strdup(temp->value);
				temp = temp->next;
			}
			cmd->argv[i] = NULL;
			continue;  // tempは既に進んでいるのでループ末尾のtemp = temp->nextをスキップ
		}
		else if (temp->type == REDIR_IN || temp->type == HEREDOC)
		{
			cmd->type = temp->type;
			temp = temp->next;
			if (temp != NULL && temp == WORD)
				cmd->infile = ft_strdup( temp->value);
		}
		else if (temp->type == REDIR_OUT || temp->type == REDIR_APPEND)
		{
			cmd->type = temp->type;
			temp = temp->next;
			if (temp != NULL && temp->type == WORD)
				cmd->outfile = ft_strdup(temp->value);
		}
		else if (temp->type == PIPE)
		{
			cmd->next = malloc(sizeof(t_cmd));
			if (cmd->next == NULL)
				return ;
			cmd = cmd->next;
			cmd->argv = NULL;
			cmd->infile = NULL;
			cmd->outfile = NULL;
			cmd->type = NO_REDIR;
			cmd->next = NULL;
		}
		temp = temp->next;
	}
	free_tokens(tokens);

	// 各コマンドのpathを検索
	while (head != NULL)
	{
		if (head->argv != NULL && head->argv[0] != NULL)
			head->path = search_path(head->argv[0], ev);
		head = head->next;
	}
}
