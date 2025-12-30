#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"


typedef struct s_cmd
{
	char	**argv;
	char	*path;
}	t_cmd;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_cmd	*cmd;
	t_env	*env;

}	t_data;



void	prompt(char **ev);
int		main(int ac, char **av, char **ev);
char	*search_path(const char *cmd, char *const envp[]);
char	**space_tab_split(const char *str);
void	free_split(char **sp);

#endif
