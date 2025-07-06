#include "minishell.h"
#include <stdio.h>

static void	print_redirections(t_redir *redir)
{
	while (redir)
	{
		printf("  Redirection: %s %s\n", redir->redir, redir->file);
		redir = redir->next;
	}
}

static void	print_cmd_list(t_cmd *cmd_list)
{
	int	i;

	while (cmd_list)
	{
		printf("Pipe: %d\n", cmd_list->pipe);
		if (cmd_list->cmd)
		{
			i = 0;
			while (cmd_list->cmd[i])
			{
				printf("  Cmd[%d]: %s\n", i, cmd_list->cmd[i]);
				i++;
			}
		}
		else
			printf("  Cmd: (null)\n");
		print_redirections(cmd_list->redirections);
		cmd_list = cmd_list->next;
	}
}

static void	free_cmd(t_cmd *cmd)
{
	int i;

	if (!cmd)
		return ;
	if (cmd->cmd)
	{
		i = 0;
		while (cmd->cmd[i])
			free(cmd->cmd[i++]);
		free(cmd->cmd);
	}
	while (cmd->redirections)
	{
		t_redir *tmp = cmd->redirections;
		cmd->redirections = cmd->redirections->next;
		free(tmp->redir);
		free(tmp->file);
		free(tmp);
	}
	free(cmd);
}

static void	free_cmd_list(t_cmd *head)
{
	t_cmd *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_cmd(tmp);
	}
}
static void	print_tokens(t_token *head)
{
	while (head)
	{
		printf("tokens:\n[%s] (%d)\n", head->token, head->is_operator);
		head = head->next;
	}
	printf("\n");
}

static void free_token(t_token *head)
{
	t_token *tmp;

	while (head != NULL)
	{
		tmp = head->next;
		free(head->token);
		free(head);
		head = tmp;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmd_list;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = tokenize(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		print_tokens(tokens);
		free(line);
		expand_token(tokens, env);
		cmd_list = parse_cmd_list(tokens);
		print_cmd_list(cmd_list);
		free_token(tokens);
		free_cmd_list(cmd_list);
	}
	return (0);
}