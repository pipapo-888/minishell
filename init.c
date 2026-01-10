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
	else
		perror("pwd");
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	return ;
}

void	built_in_env(t_env *env)
{
	char	**arr;
	int		i;

	arr = env_to_array(env);
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

int	argument_count(char **argv)
{
	int	count;

	count = 0;
	while (argv[count] != NULL)
		count++;
	return (count);
}

void	built_in_cd(t_cmd *cmd, char **ev)
{
	char	*path;

	if (argument_count(cmd->argv) > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return ;
	}
	path = NULL;
	if (cmd->argv[1] == NULL || ft_strcmp(cmd->argv[1], "~") == 0)
	{
		path = get_env_value(ev, "HOME");
		if (path == NULL)
			return (perror("cd: HOME not set"));
	}
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		path = get_env_value(ev, "OLDPWD");
		if (path == NULL)
			return (perror("cd: OLDPWD not set"));
	}
	if (path != NULL)
	{
		if (chdir(path) != 0)
			return (perror("cd"));
		return ;
	}
	if (chdir(cmd->argv[1]) != 0)
		return (perror("cd"));
}

// int	built_in_check(t_cmd *cmd, char **ev)
// static void	remove_env_node(t_data *data, t_env *prev, t_env *current)
// {
// 	if (prev == NULL)
// 		data->env = current->next;
// 	else
// 		prev->next = current->next;
// 	free(current->key);
// 	free(current->value);
// 	free(current);
// }

static t_env	*find_key(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static t_env	*create_export_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else 
		node->value = NULL;
	node->type = SHOW;
	node->next = NULL;
	return (node);
}

static void	add_env_back(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

static void	export_one(t_data *data, char *arg)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	t_env	*existing;
	t_env	*new_node;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		key = ft_substr(arg, 0, equal_pos - arg);
		value = ft_strdup(equal_pos + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	existing = find_key(data->env, key);
	if (existing)
	{
		free(existing->value);
		existing->value = value;
		existing->type = SHOW;
		free(key);
	}
	else
	{
		new_node = create_export_node(key, value);
		add_env_back(&data->env, new_node);
		free(key);
		if (value)
			free(value);
	}
}

void	built_in_export(t_data *data, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		export_one(data, argv[i]);
		i++;
	}
}

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
				break ;

			}
			current = current->next;
		}
		i++;
	}
}

int	built_in_check(t_cmd *cmd, t_data *data, char **ev)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (built_in_echo(cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (built_in_cd(cmd, ev), 0);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (built_in_pwd(cmd), 0);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (built_in_export(data, cmd->argv), 0);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (built_in_unset(data, cmd->argv), 0);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (built_in_env(data->env), 0);
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
