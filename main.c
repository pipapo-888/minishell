#include "./minishell.h"

void	ft_execve(char *path, char **argv, char **ev)
{
	pid_t	pid;

	pid = fork();
	printf("%d\n", pid);
	if (pid == 0)
	{
		execve(path, argv, ev);
		perror("execve");
		exit(1);
	}
	else
	{
		wait(NULL);
	}
}

int	check_input(char *input, char **argv)
{
	(void)input;
	if (!ft_strcmp(argv[0], "cd"))
	{
		chdir(argv[1]);
		return (0);
	}
	if (!ft_strcmp(argv[0], "exit"))
	{
		exit(1);
	}
	if (!ft_strcmp(argv[0], "export"))
	{
		printf("export実装前\n");
		return (0);
	}
	if (!ft_strcmp(argv[0], "echo"))
	{
		printf("echo実装前\n");
		return (0);
	}
	return (1);
}

void	prompt(char **ev)
{
	char	*input;
	char	**argv;
	char	*path;

	input = readline("minishell$ ");
	// printf("input: %s\n", input);
	if (*input)
		argv = space_tab_split(input);
	// printf("path: %s\n", path);
	path = search_path(argv[0], ev);
	if (input != NULL)
	{
		// printf("input[0]: %s\n", input);
		path = search_path(argv[0], ev);
		if (!check_input(input, argv))
			return ;
		ft_execve(path, argv, ev);
	}
	else
	{
		printf("%s\n", input);
	}
	free(input);
}

int	main(int ac, char **av, char **envp)
{
	char	*program_name;

	// t_data	data;
	// int	i;
	// int	length;
	// i = 0;
	// data.cmd = NULL;
	// while (ev[i] != NULL)
	// {
	// 	length = ft_strlen(ev[i]);
	// 	data.env = ft_substr(ev[i], 0, length);
	// 	i++;
	// }
	// program_name = av[0];
	(void)ac;
	(void)av;
	(void)program_name;
	(void)envp;
	while (1)
	{
		prompt(envp);
	}
	// exit(1);
	return (0);
}

// cd exit history echo
