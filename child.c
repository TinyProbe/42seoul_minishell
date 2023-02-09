/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:02:43 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 03:22:33 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	setchild(t_a *a, t_i32 *fd);
static void	applyarg(t_a *a, t_i32 *fd);

void	child(t_a *a, t_i32 *fd)
{
	setchild(a, fd);
	program(a);
	output(a, a->fd[STDOUT__], a->fd[STDERR__]);
	exit(0);
}

static void	setchild(t_a *a, t_i32 *fd)
{
	a->dup2_cnt_old = a->dup2_cnt;
	a->fd[STDOUT__] = fd[1];
	a->fd[STDERR__] = fd[1];
	close(fd[0]);
	a->buf_l = 0;
	if (a->cmd_l == 0)
		applyarg(a, fd);
}

static void	applyarg(t_a *a, t_i32 *fd)
{
	if (a->conj == CONJ_OR)
	{
		a->fd[STDIN__] = fd[2];
		close(fd[3]);
	}
	redirect(a);
}
