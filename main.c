#include "./minishell.h"
#include <signal.h>

void	ft_execve(t_cmd *cmd, char **ev)
{
	pid_t	pid;

	// printf("PATH: %s\n", cmd->path);
	// printf("ARGV[0]: %s\n", cmd->argv[0]);
	// printf("ARGV[1]: %s\n", cmd->argv[1]);
	if (built_in_check(cmd, ev) == 0)
		return ;
	pid = fork();
	printf("%d\n", pid);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL); // SIGQUIT
		signal(2, SIG_DFL);       // SIGINT
		setup_redirects(cmd);
		execve(cmd->path, cmd->argv, ev);
		perror("execve");
		exit(1);
	}
	else
	{
		wait(NULL);
	}
}

void	prompt(char **ev, t_data data)
{
	data.cmd = malloc(sizeof(t_cmd));
	if (data.cmd == NULL)
		return ;
	data.input = readline("minishell$ ");
	if (data.input == NULL || data.input[0] == '\0')
	{
		free(data.input);
		free(data.cmd);
		if (data.input == NULL)
			exit(1);
		return ;
	}
	add_history(data.input);
	cmd_init(data.cmd, data.input, ev);
	if (data.cmd->argv == NULL)
	{
		free(data.input);
		free(data.cmd);
		return ;
	}
	ft_execve(data.cmd, ev);
	free_split(data.cmd->argv);
	free(data.cmd->path);
	free(data.cmd);
	free(data.input);
}

void	handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	char	*tmp;
	int		size;
	int		i;

	size = env_list_size(env);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->key, "=");
			arr[i] = ft_strjoin(tmp, env->value);
			free(tmp);
		}
		else
			arr[i] = ft_strdup(env->key);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static t_env	*create_env_node(char *envp_line)
{
	t_env	*node;
	char	*equal_pos;
	int		key_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_pos = ft_strchr(envp_line, '=');
	if (equal_pos)
	{
		key_len = equal_pos - envp_line;
		node->key = ft_substr(envp_line, 0, key_len);
		node->value = ft_strdup(equal_pos + 1);
	}
	else
	{
		node->key = ft_strdup(envp_line);
		node->value = NULL;
	}
	node->next = NULL;
	return (node);
}

static void	env_add_back(t_env **head, t_env *new_node)
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

void	env_init(t_data *data, char **envp)
{
	t_env	*new_node;
	int		i;

	i = 0;
	data->env = NULL;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (new_node)
			env_add_back(&data->env, new_node);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*program_name;
	t_data	data;

	env_init(&data, envp);

	(void)ac;
	(void)av;
	(void)program_name;
	data.cmd = NULL;
	data.env = NULL;
	data.input = NULL;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt(envp, data);
	}
	// exit(1);
	return (0);
}

// cd exit history echo
