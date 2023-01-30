/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:22:02 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 12:58:04 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	rein(t_z *z);
static void	heredoc(t_z *z, t_i32 i);
static void	reout(t_z *z);

void	redirect(t_z *z)
{
	rein(z);
	reout(z);
}

static void	rein(t_z *z)
{
	t_i32	i;

	i = 0;
	while (i < z->ri_len)
	{
		if (z->fd[STDIN__] > STDERR__)
			close(z->fd[STDIN__]);
		if (ft_strlen(z->ri[i]) == 1)
			z->fd[STDIN__] = open(z->ri[i + 1], O_RDONLY);
		else
			heredoc(z, i);
		if (z->fd[STDIN__] == -1)
		{
			z->errno = ERRNO_FILEPATH;
			z->errarg = z->ri[i + 1];
			error(z);
		}
		i += 2;
	}
}

static void	heredoc(t_z *z, t_i32 i)
{
	t_i8	*s;
	t_i32	fd[2];

	pipe(fd);
	while (TRUE)
	{
		s = ft_gnl(STDIN__);
		if (!ft_strncmp(s, z->ri[i + 1], ft_strlen(z->ri[i + 1])))
			break ;
		write(fd[1], s, ft_strlen(s));
		free(s);
	}
	free(s);
	close(fd[1]);
	z->fd[STDIN__] = fd[0];
}

static void	reout(t_z *z)
{
	t_i32	i;

	i = 0;
	while (i < z->ro_len)
	{
		if (z->fd[STDOUT__] > STDERR__)
			close(z->fd[STDOUT__]);
		if (ft_strlen(z->ro[i]) == 1)
			z->fd[STDOUT__] = open(
					z->ro[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			z->fd[STDOUT__] = open(
					z->ro[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (z->fd[STDIN__] == -1)
		{
			z->errno = ERRNO_FILEFAIL;
			z->errarg = z->ro[i + 1];
			error(z);
		}
		i += 2;
	}
}
