/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoale <hoale@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:17:35 by hoale             #+#    #+#             */
/*   Updated: 2025/03/22 17:29:01 by hoale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Check the if argument is closed by quotes
//The integration can be applied for parsing the arguments
int	is_closed_arg(char *start, t_data data)
{
	int	i;
	char	prev;
	int	in_quote1;
	int	in_quote2;

	i = 0;
	prev = ' ';
	in_quote1 = 0;
	in_quote2 = 0;
	while (start[i] == ' ')
		i++ ;
	while (start[i] && in_quote1 != 2 && in_quote2 != 2)
	{
		if (start[i] == '\'' && prev != '\\' && in_quote2 == 0)
			in_quote1++;
		if (start[i] == '\"' && prev != '\\' && in_quote1 == 0)
			in_quote2++;
		if (start[i] == ' ' && prev != '\\' && in_quote1 == 0 && in_quote2 == 0)
			break;
		prev = start[i];
		i++ ;
	}
	if (in_quote1 == 2 || in_quote2 == 2 || (in_quote1 == 0 && in_quote2 == 0))
		return (1);
	return (0);
}

//Count number of pipes in input
int	pipe_count(char *input)
{
	int		count;
	int		i;
	char	prev;

	i = 0;
	count = 0;
	prev = '|';
	if (!input)
		return (0);
	while (input[i])
	{
		if (prev == '|' && input[i] != '|')
			count++ ;
		prev = input[i];
		i++ ;
	}
	return (count);
}


// int token_count(char *pipe)
// {
// 	char	*ptr;
// 	int		count;
// 	char	prev;

// 	if (!pipe)
// 		return (0);
// 	ptr = pipe;
// 	while (ptr)
// 	{
// 		if (ft_strncmp(ptr, "<") == 0 || ft_strncmp(ptr, "<<") == 0)
// 		ptr++ ;
// 	}
// }

// int	redirect_count(char *pipe)
// {
// 	int	count;
// 	char	prev;
// 	char	next;
// 	int	i;

// 	i = 0;
// 	while(pipe[i+1])
// 	{
// 		if (i != 0)
// 			prev == pipe[i - 1];
// 		next = pipe[i + 1];
// 		if ((pipe[i] == '<' || pipe[i] == '>') && (prev != '<') &&)
// 	}
// }

#include <stdio.h>
int main(int ac, char **av, char **env)
{
	char	*input = NULL;
	
	while(1)
	{
		input = readline("minishell$ ");
		if(!input)
		{
			printf("control d\n");
			break;
		}
		printf("%i\n", is_closed_arg(input, env));
	}
	return(0);
}