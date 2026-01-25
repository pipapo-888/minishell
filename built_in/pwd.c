#include "../minishell.h"

#define PATHNAME_SIZE 1024

void	built_in_pwd(t_cmd *cmd)
{
	char	pathName[PATHNAME_SIZE];
	int		saved_stdout;

	saved_stdout = -1;
	ft_memset(pathName, '\0', PATHNAME_SIZE);
	if (cmd->type != NO_REDIR)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (saved_stdout < 0)
		{
			write(2, "minishell: ", 12);
			perror("dup");
			return ;
		}
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
		if (dup2(saved_stdout, STDOUT_FILENO) < 0)
		{
			write(2, "minishell: ", 12);
			perror("dup2");
		}
		close(saved_stdout);
	}
	return ;
}
