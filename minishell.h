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

typedef struct s_redir
{
	char			*redir;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd;
	t_redir			*redirections;
	int				pipe;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char	*token;
	int		is_operator;
	struct s_token	*next;
}	t_token;

t_token	*tokenize(const char *s);
void	expand_token(t_token *token, char **envp);
t_cmd	*parse_cmd_list(t_token *tokens);
void 	free_token(t_token *head);
void	free_cmd_list(t_cmd *head);
t_cmd	*parse(char *line, char **env);

#endif