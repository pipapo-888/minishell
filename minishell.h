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

typedef enum e_export_type
{
	SHOW,
	DONT_SHOW
}	t_export_type;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	NO_REDIR
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_cmd
{
	char			**argv;
	char			*path;
	char			*infile;
	char			*outfile;
	t_token_type	type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	t_export_type	type;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_cmd	*cmd;
	t_env	*env;
	char	*input;

}	t_data;

void	prompt(char **ev, t_data data);
char	*search_path(const char *cmd, char *const envp[]);
char	**space_tab_split(const char *str);
void	free_split(char **sp);
char	*get_env_value(char *const envp[], const char *key);
void	setup_redirects(t_cmd *cmd);
int		built_in_check(t_cmd *cmd, t_data *data, char **ev);
void	built_in_unset(t_data *data, char **argv);
void	cmd_init(t_cmd *cmd, char *input, char **ev);
void	env_init(t_data *data, char **envp);
char	**env_to_array(t_env *env);

t_token	*extract_quoted_token(const char *input, int *len);
t_token	*extract_pipe_token(const char *input, int *len);
t_token	*extract_redirect_token(const char *input, int *len);
t_token	*extract_word_token(const char *input, int *len);
t_token	*tokenize(const char *input);
void	free_tokens(t_token *tokens);
int		skip_spaces(const char *input);

#endif
