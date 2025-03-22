/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoale <hoale@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:59:04 by hoale             #+#    #+#             */
/*   Updated: 2025/03/19 12:36:57 by hoale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "fcntl.h"

//Handle ">" (Overwrite output to the file)
void	redir_right(char *out, char *path)
{
	int	fd;
	int	i;
	ssize_t	bytes;

	i = 0;
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
		return(ft_putstr_fd("Cannot open file.\n", 2));
	bytes = write(fd, out, ft_strlen(out) + 1);
	if (bytes < 0)
	{
		close(fd);
		return(ft_putstr_fd("Cannot overwrite file.\n", 2));
	}
	close(fd);
}

//Handle ">>" (Append output to the file)
void	redir_doub_right(char *out, char *path)
{
	int	fd;
	int	i;
	ssize_t	bytes;

	i = 0;
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND);
	if (fd < 0)
		return(ft_putstr_fd("Cannot open file.\n", 2));
	bytes = write(fd, out, ft_strlen(out) + 1);
	if (bytes < 0)
	{
		close(fd);
		return(ft_putstr_fd("Cannot overwrite file.\n", 2));
	}
	close(fd);
}

//Handle "<" (Return content of the file as input)
char	*input(char *path)
{
	int fd;
	ssize_t	bytes;
	char	*input;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return(ft_putstr_fd("Cannot open file.\n"), NULL);
	
}

