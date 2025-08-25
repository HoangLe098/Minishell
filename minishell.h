#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_data
{
	char	**env;
	char	**my_env;
	char	**export_list;
	char	**path;
	int		pipe1[2];
	int		pipe2[2];
	int		file[2];
	int		first;
	int		o_stdin;
	int		o_stdout;
	int		status;
}	t_data;

typedef struct s_redir
{
	char			*redir;
	char			*file;
	int				expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd;
	t_redir			*redirs;
	int				pipe;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char			*token;
	int				is_op;
	struct s_token	*next;
}	t_token;

typedef struct s_dollar_ctx
{
	const char	*s;
	int			*i;
	t_token		**head;
	int			expand;
	int			heredoc_mode;
}	t_dollar_ctx;

int		is_valid_var_char(char c);
int		is_op_char(char c);
t_token	*new_tok(const char *s, size_t len, int is_op);
int		append_token(t_token **head, t_token *node);
int		tokenize_dollar_status(t_dollar_ctx *ctx, int start);
int		tokenize_dollar(t_dollar_ctx *ctx, int out_single);
int		tokenize_quotes_or_dollar(t_dollar_ctx *ctx);
t_token	*tokenize(char *s);
char	*ft_strjoin_free(char *s1, char *s2);
int		append_char(char **dst, char c);
char	*get_env_value(char *key, char **envp);
char	*expand_node(char *input, t_data *data);
void	expand_token(t_token **tokens, t_data *data);
void	simplify_tokens(t_token **head);
int		fill_redirections(t_cmd *cmd, t_token *start, t_token *end);
char	**fill_cmd_array(t_token **cur);
t_cmd	*parse_cmd_list(t_token *tokens);
void	free_token(t_token *head);
void	free_cmd_list(t_cmd *head);
t_cmd	*parse(char *line, t_data *data);

#endif