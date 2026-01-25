#include "../minishell.h"

int	dup2_and_close(int fd, int flag)
{
	if (dup2(fd, flag) == -1)
	{
		write(2, "minishell: ", 12);
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
