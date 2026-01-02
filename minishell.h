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
# include <fcntl.h>

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_cmd
{
	char			**argv;
	char			*path;
	char			*infile;
	char			*outfile;
	t_redir_type	type;
	struct s_cmd	*next;
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
	char	*input;

}	t_data;



void	prompt(char **ev);
int		main(int ac, char **av, char **ev);
char	*search_path(const char *cmd, char *const envp[]);
char	**space_tab_split(const char *str);
void	free_split(char **sp);
char	*get_env_value(char *const envp[], const char *key);
void	parse_redirects(t_cmd *cmd, char **argv);
void	setup_redirects(t_cmd *cmd);
char	**filter_redirects(char **argv);
int		built_in_check(t_cmd *cmd, char **ev);
void	cmd_init(t_cmd *cmd, char *input, char **ev);
char	**filter_redirects(char **argv);

#endif
