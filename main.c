/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 13:00:22 by habe              #+#    #+#             */
/*   Updated: 2025/12/28 19:47:44 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	prompt(char **ev)
{
	char	*input;
	char	**argv;
	char	*path;
	pid_t	pid;

	input = readline("minishell$ ");
	// printf("path: %s\n", path);
	if (*input)
		argv = space_tab_split(input);
	printf("input: %s\n", input);
	path = search_path(argv[0], ev);
	printf("path: %s\n", path);
	if (input != NULL)
	{
		printf("input[0]: %s\n", input);
		argv = space_tab_split(input);
		path = search_path(argv[0], ev);
		if (!ft_strcmp(argv[0], "cd"))
		{
			chdir(argv[1]);
			return ;
		}
		if (!ft_strcmp(argv[0], "exit"))
		{
			exit(1);
		}
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

	while (1)
	{
		prompt(ev);
	}
	// exit(1);
	return (0);
}

// cd exit history echo
