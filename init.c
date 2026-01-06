#include "./minishell.h"

#define PATHNAME_SIZE 1024

static int	is_n_flag(char *str)
{
	int	i;

	if (str == NULL || str[0] != '-')
		return (0);
	i = 1;
	if (str[i] == '\0')
		return (0);
	while(str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	built_in_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;
	int	saved_stdout;

	saved_stdout = -1;
	i = 1;
	n_flag = 0;
	while (cmd->argv[i] && is_n_flag(cmd->argv[i]))
	{
		n_flag = 1;
		i++;
	}
	if (cmd->type != NO_REDIR)
	{
		saved_stdout = dup(STDOUT_FILENO);
		setup_redirects(cmd);
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
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
	{
		ft_putstr_fd(pathName, 1);
		write(1, "\n", 1);
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
	if (!ft_strcmp(cmd->argv[0], "exit"))
		exit(1);
	return (1);
}

void	put_in_cmd(t_cmd *cmd, t_token *tokens)
{
	t_token	*temp;
	t_token	*counter;
	int		i;
	int		word_count;

	temp = tokens;
	word_count = 0;
	i = 0;
	while (temp != NULL)
	{
		if (temp->type == WORD)
		{
			counter = temp;

			while (counter != NULL && counter->type == WORD)
			{
				word_count++;
				counter = counter->next;
			}

			cmd->argv = malloc(sizeof(char *) * (word_count + 1));
			if (cmd->argv == NULL)
				return ;

			while (temp != NULL && temp->type == WORD)
			{
				cmd->argv[i] = ft_strdup(temp->value);
				i++;
				temp = temp->next;
			}
			cmd->argv[i] = NULL;
		}
		else if (temp->type == REDIR_IN || temp->type == HEREDOC)
		{
			cmd->type = temp->type;
			temp = temp->next;
			if (temp != NULL && temp == WORD)
				cmd->infile = ft_strdup( temp->value);
			temp = temp->next;
		}
		else if (temp->type == REDIR_OUT || temp->type == REDIR_APPEND)
		{
			cmd->type = temp->type;
			temp = temp->next;
			if (temp != NULL && temp->type == WORD)
				cmd->outfile = ft_strdup(temp->value);
			temp = temp->next;
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
			temp = temp->next;
		}
	}
}

void	put_in_path(t_cmd *cmd, char **ev)
{
	t_cmd	*head;

	head = cmd;
	while (head != NULL)
	{
		if (head->argv != NULL && head->argv[0] != NULL)
			head->path = search_path(head->argv[0], ev);
		head = head->next;
	}
}

void	cmd_init(t_cmd *cmd, char *input, char **ev)
{
	t_token	*tokens;

	tokens = tokenize(input);
	if (tokens == NULL)
		return ;
	put_in_cmd(cmd, tokens);
	free_tokens(tokens);
	put_in_path(cmd, ev);
}
