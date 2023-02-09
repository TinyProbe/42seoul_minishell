/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:18:53 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 03:45:59 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	setself(t_a *a, t_i32 *fd)
{
	t_i32	fd2[2];

	pipe(fd2);
	a->fd_old[STDIN__] = a->fd[STDIN__];
	a->fd_old[STDOUT__] = a->fd[STDOUT__];
	a->fd_old[STDERR__] = a->fd[STDERR__];
	if (a->conj == CONJ_OR)
	{
		output(a, fd2[1], a->fd[STDERR__]);
		a->fd[STDIN__] = fd2[0];
	}
	else
	{
		output(a, a->fd[STDOUT__], a->fd[STDERR__]);
		close(fd2[0]);
	}
	close(fd2[1]);
	a->fd[STDOUT__] = fd[1];
	redirect(a);
}

void	recover(t_a *a, t_i32 *fd)
{
	if (a->fd[STDIN__] != a->fd_old[STDIN__])
	{
		close(a->fd[STDIN__]);
		a->fd[STDIN__] = a->fd_old[STDIN__];
	}
	if (a->fd[STDOUT__] != a->fd_old[STDOUT__])
	{
		close(a->fd[STDOUT__]);
		a->fd[STDOUT__] = a->fd_old[STDOUT__];
	}
	if (a->fd[STDERR__] != a->fd_old[STDERR__])
	{
		close(a->fd[STDERR__]);
		a->fd[STDERR__] = a->fd_old[STDERR__];
	}
	a->buf_l = read(fd[0], a->buf, BUF_MAX);
	close(fd[0]);
}
