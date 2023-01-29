/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:02:43 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 14:43:57 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	setchild(t_z *z, t_i32 *fd);
static void	applyarg(t_z *z, t_i32 *fd);

void	child(t_z *z, t_i32 *fd)
{
	setchild(z, fd);
	program(z);
	output(z, z->fd[STDOUT__], z->fd[STDERR__]);
	exit(0);
}

static void	setchild(t_z *z, t_i32 *fd)
{
	z->fd[STDOUT__] = fd[1];
	z->fd[STDERR__] = fd[1];
	close(fd[0]);
	z->buf_len = 0;
	if (z->len == 0)
		applyarg(z, fd);
}

static void	applyarg(t_z *z, t_i32 *fd)
{
	if (z->conj == CONJ_OR)
	{
		z->fd[STDIN__] = fd[2];
		close(fd[3]);
	}
	redirect(z);
}
