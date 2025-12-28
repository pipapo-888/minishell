/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 13:00:22 by habe              #+#    #+#             */
/*   Updated: 2025/12/28 15:00:58 by habe             ###   ########.fr       */
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
	argv = space_tab_split(input);
	printf("input: %s\n", input);
	path = search_path(argv[0], ev);
	printf("path: %s\n", path);
	if (input != NULL && path != NULL)
	{
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
		// execve(input, argv, env);

	}
	else
	{
		printf("%s\n", input);
	}
	free(input);
}

int	main(int ac, char **av, char **ev)
{
	char	*program_name;

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
