#include "minishell.h"

static int	tokenize_space(const char *s, int *i, t_token **head)
{
	if (s[*i] != ' ')
		return (0);
	if (!append_token(head, new_tok(" ", 1, 3)))
		return (-1);
	(*i)++;
	return (1);
}

static int	tokenize_operator(const char *s, int *i, t_token **head)
{
	if (!is_op_char(s[*i]))
		return (0);
	if ((s[*i] == '<' || s[*i] == '>') && s[*i + 1] == s[*i])
	{
		if (!append_token(head, new_tok(&s[*i], 2, 1)))
			return (-1);
		*i += 2;
	}
	else
	{
		if (!append_token(head, new_tok(&s[*i], 1, 1)))
			return (-1);
		(*i)++;
	}
	return (1);
}

static int	tokenize_unquoted_word(const char *s, int *i, t_token **head)
{
	int	start;

	start = *i;
	while (s[*i] && s[*i] != ' ' && !is_op_char(s[*i])
		&& s[*i] != '\'' && s[*i] != '"' && s[*i] != '$')
		(*i)++;
	if (start < *i)
	{
		if (!append_token(head, new_tok(&s[start], *i - start, 0)))
			return (-1);
		else
			return (1);
	}
	return (0);
}

static int	tokenize_step(const char *s, int *i, t_token **head)
{
	int	ret;

	ret = tokenize_space(s, i, head);
	if (ret == -1)
		return (-1);
	if (ret)
		return (1);
	ret = tokenize_operator(s, i, head);
	if (ret == -1)
		return (-1);
	if (ret)
		return (1);
	ret = tokenize_quotes_or_dollar(s, i, head);
	if (ret == -1)
		return (-1);
	if (ret)
		return (1);
	if (!tokenize_unquoted_word(s, i, head))
		return (-1);
	return (1);
}

t_token	*tokenize(const char *s)
{
	t_token	*head;
	int		i;
	int		ret;

	head = NULL;
	i = 0;
	while (s[i])
	{
		ret = tokenize_step(s, &i, &head);
		if (ret == -1)
		{
			free_token(head);
			return (NULL);
		}
	}
	return (head);
}
