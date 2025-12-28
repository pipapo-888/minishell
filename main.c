/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 13:00:22 by habe              #+#    #+#             */
/*   Updated: 2025/12/28 13:05:21 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <aio.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> // wait用
#include <unistd.h>

void	prompt(char **ev)
{
	char	*input;
	char	*argv[3];
	pid_t	pid;

	input = readline("minishell$ ");
	if (*input)
	{
		if (input[0] == 'l' && input[1] == 's')
		{
			argv[0] = "/usr/bin/ls"; // 実行ファイルのパス
			argv[1] = "-l";
			argv[2] = NULL;
			pid = fork();
			printf("%d\n", pid);
			if (pid == 0)
			{
				// printf("%d\n", pid);
				// ここは子プロセス：lsに変身する
				execve(argv[0], argv, ev);
				// もしexecveが失敗したらここに来る
				perror("execve");
				exit(1);
			}
			else
			{
				// ここは親プロセス（minishell）：子が終わるのを待つ
				wait(NULL);
			}
			// execve(input, argv, env);
		}
		else
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
