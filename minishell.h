#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR 1
# define SHELL_ERROR 2
# define ACCESS_DENY 126
# define NO_COMMAND 127
# define SIG_INT_FAIL 130

typedef enum e_export_type
{
	SHOW,
	EXPAND,
	DONT_SHOW
}						t_export_type;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	NO_REDIR
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	int					quoted;
	struct s_token		*next;
}						t_token;

typedef struct s_heredoc
{
	char				*content;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_cmd
{
	char				**argv;
	char				*path;
	char				*infile;
	char				*outfile;
	t_heredoc			*heredoc;
	t_token_type		type;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_env
{
	char				*key;
	char				*value;
	t_export_type		type;
	struct s_env		*next;
}						t_env;

typedef struct s_data
{
	t_cmd				*cmd;
	t_env				*env;
	char				*input;
}						t_data;

// prompt
void					prompt(t_data data);
void					ft_execve(t_cmd *cmd, t_data *data, char **ev);
char					*free_strjoin(char *str1, char *str2);

// env
void					env_init(t_data *data, char **envp);
char					**env_to_array(t_env *env, t_export_type type);
void					env_add_back(t_env **head, t_env *new_node);
int						env_list_size(t_env *env);
void					add_new_env(t_data *data, char *key, char *value);
t_env					*find_key(t_env *env, char *key);

// expand
int						get_var_len(char *str);
int						is_valid_variable_char(char c, int first);
char					*expand_variables(char *str, t_env *env);
char					*expand_single_var(char *str, int *i, t_env *env);

// cmd_init
void					cmd_setup(t_data *data, t_cmd *cmd, char *input,
							char **ev);
void					cmd_init(t_data *data);
void					put_in_cmd(t_data *data, t_cmd *cmd, t_token **tokens);
t_cmd					*get_last_cmd(t_data *data);

// tokenizer
int						extract_quoted_token(const char *input,
							t_token **token);
int						extract_pipe_token(t_token **token);
int						extract_redirect_in(t_token **token);
int						extract_redirect_out(const char *input,
							t_token **token);
int						extract_word_token(const char *input, t_token **token);
int						extract_heredoc(t_token **token);
t_token					*tokenize(const char *input);
void					free_tokens(t_token *tokens);

// heredoc
void					ft_heredoc(t_cmd *cmd, char *key, int quoted,
							t_env *env);
int						handle_heredoc(t_data *data, t_cmd *cmd, t_token **temp);

// built-in
int						built_in_check(t_cmd *cmd, t_data *data);
void					built_in_cd(t_cmd *cmd, char **ev, t_data *data);
void					built_in_echo(t_data *data, t_cmd *cmd);
void					built_in_env(t_data *data, t_cmd *cmd);
void					built_in_export(t_data *data, char **argv);
void					built_in_pwd(t_data *data, t_cmd *cmd);
void					built_in_unset(t_data *data, char **argv);

// utils
int						dup2_and_close(int fd, int flag);
void					set_exit_status(t_env *env, int status);
int						open_infile(const char *infile);
int						open_outfile(const char *outfile, t_token_type type);
int						setup_redirects(t_cmd *cmd);
int						save_and_redirects(t_cmd *cmd, int *saved_stdout);
char					*search_path(const char *cmd, char *const envp[]);
char					*get_env_value(char *const envp[], const char *key);
char					*ft_strjoin_char(char *str, char c);

// free
void					free_split(char **sp);
void					free_all(t_data *data);

#endif
