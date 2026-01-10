#include "../minishell.h"

void dup2_and_close(int fd, int flag)
{
	dup2(fd, flag);
	close(fd);
}
