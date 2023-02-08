/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:01:20 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 02:58:10 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	setparent(t_a *a, t_i32 *fd);
static void	clearparent(t_a *a, t_i32 *fd);

void	parent(t_a *a, t_i32 *fd, pid_t pid)
{
	setparent(a, fd);
	waitpid(pid, &(a->rtn), 0);
	a->rtn /= 256;
	a->buf_l = read(a->fd[STDIN__], a->buf, BUF_MAX);
	clearparent(a, fd);
}

static void	setparent(t_a *a, t_i32 *fd)
{
	a->fd[STDIN__] = fd[0];
	close(fd[1]);
	close(fd[2]);
	if (a->conj == CONJ_OR)
		output(a, fd[3], a->fd[STDERR__]);
	else
		output(a, a->fd[STDOUT__], a->fd[STDERR__]);
	close(fd[3]);
}

static void	clearparent(t_a *a, t_i32 *fd)
{
	a->fd[STDIN__] = STDIN__;
	close(fd[0]);
}
