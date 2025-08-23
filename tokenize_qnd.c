#include "minishell.h"

static int	tokenize_double_quote(const char *s, int *i, t_token **head)
{
	int	start;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
		{
			if (start < *i
				&& (!append_token(head, new_tok(&s[start], *i - start, 0))))
				return (-1);
			if (tokenize_dollar(s, i, head, 1) == -1)
				return (-1);
			start = *i;
			continue ;
		}
		(*i)++;
	}
	if (start < *i && (!append_token(head, new_tok(&s[start], *i - start, 0))))
		return (-1);
	else if (s[*i] == '"' && (!append_token(head, new_tok("", 0, 0))))
		return (-1);
	if (s[*i] == '"')
		(*i)++;
	return (1);
}

/* handle 'single quoted' section: produce one literal token (no expansion) */
static int	tokenize_single_quote(const char *s, int *i, t_token **head)
{
	int		start;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (start < *i)
	{
		if (!append_token(head, new_tok(&s[start], *i - start, 0)))
			return (-1);
	}
	else if (s[*i] == '\'')
	{
		if (!append_token(head, new_tok("", 0, 0)))
			return (-1);
	}
	if (s[*i] == '\'')
		(*i)++;
	return (1);
}

int	tokenize_quotes_or_dollar(const char *s, int *i, t_token **head)
{
	if (s[*i] == '"')
		return (tokenize_double_quote(s, i, head));
	if (s[*i] == '\'')
		return (tokenize_single_quote(s, i, head));
	if (s[*i] == '$')
		return (tokenize_dollar(s, i, head, 1));
	return (0);
}
