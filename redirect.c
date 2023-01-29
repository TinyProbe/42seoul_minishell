/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 01:22:02 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 14:43:57 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	rein(t_z *z);
static void	heredoc(t_z *z);
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
			heredoc(z);
		if (z->fd[STDIN__] == -1)
		{
			z->errno = ERRNO_FILEPATH;
			error(z);
		}
		i += 2;
	}
}

static void	heredoc(t_z *z)
{
	(void) z;
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
					z->ri[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			z->fd[STDOUT__] = open(
					z->ri[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (z->fd[STDIN__] == -1)
		{
			z->errno = ERRNO_FILEFAIL;
			error(z);
		}
		i += 2;
	}
}
