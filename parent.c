/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:01:20 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 14:43:57 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	setparent(t_z *z, t_i32 *fd);
static void	clearparent(t_z *z, t_i32 *fd);
static void	exitsh(t_z *z);

void	parent(t_z *z, t_i32 *fd, pid_t pid)
{
	setparent(z, fd);
	waitpid(pid, &(z->rtn), 0);
	z->buf_len = read(z->fd[STDIN__], z->buf, BUF_MAX);
	clearparent(z, fd);
	if (z->rtn == EXIT)
		exitsh(z);
}

static void	setparent(t_z *z, t_i32 *fd)
{
	z->fd[STDIN__] = fd[0];
	close(fd[1]);
	if (z->conj == CONJ_OR)
	{
		output(z, fd[3], z->fd[STDERR__]);
		close(fd[2]);
		close(fd[3]);
	}
}

static void	clearparent(t_z *z, t_i32 *fd)
{
	z->fd[STDIN__] = STDIN__;
	close(fd[0]);
	if (z->conj != CONJ_OR)
	{
		close(fd[2]);
		close(fd[3]);
	}
}

static void	exitsh(t_z *z)
{
	output(z, z->fd[STDOUT__], z->fd[STDERR__]);
	if (z->fd[STDERR__] != STDERR__)
		exit(z->rtn);
	else
		exit(0);
}
