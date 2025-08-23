#include "minishell.h"

static int	tokenize_dollar_pid(t_dollar_ctx *ctx)
{
	(*ctx->i)++;
	if (!append_token(ctx->head, new_tok("$$", 2, ctx->expand)))
		return (-1);
	return (1);
}

static int	tokenize_dollar_quoted(t_dollar_ctx *ctx, int start)
{
	char	q;

	q = ctx->s[(*ctx->i)++];
	while (ctx->s[*ctx->i] && ctx->s[*ctx->i] != q)
		(*ctx->i)++;
	if (ctx->s[*ctx->i] == q)
		(*ctx->i)++;
	if (!append_token(ctx->head,
			new_tok(&ctx->s[start], *ctx->i - start, ctx->expand)))
		return (-1);
	return (1);
}

static int	tokenize_dollar_invalid(t_dollar_ctx *ctx, int start)
{
	if (!append_token(ctx->head, new_tok(&ctx->s[start], 1, 0)))
		return (-1);
	return (1);
}

static int	tokenize_dollar_var(t_dollar_ctx *ctx, int start)
{
	while (ctx->s[*ctx->i] && is_valid_var_char(ctx->s[*ctx->i]))
		(*ctx->i)++;
	if (!append_token(ctx->head,
			new_tok(&ctx->s[start], *ctx->i - start, ctx->expand)))
		return (-1);
	return (1);
}

int	tokenize_dollar(const char *s, int *i, t_token **head, int out_single)
{
	int				start;
	t_dollar_ctx	ctx;

	start = *i;
	(*i)++;
	ctx.s = s;
	ctx.i = i;
	ctx.head = head;
	if (out_single)
		ctx.expand = 2;
	else
		ctx.expand = 0;
	if (s[*i] == '?')
		return (tokenize_dollar_status(&ctx, start));
	else if (s[*i] == '$')
		return (tokenize_dollar_pid(&ctx));
	else if (s[*i] == '\'' || s[*i] == '"')
		return (tokenize_dollar_quoted(&ctx, start));
	else if (!is_valid_var_char(s[*i]))
		return (tokenize_dollar_invalid(&ctx, start));
	else
		return (tokenize_dollar_var(&ctx, start));
}
