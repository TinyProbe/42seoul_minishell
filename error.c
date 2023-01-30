/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:33 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 13:48:49 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	display(t_a *a);

void	error(t_a *a)
{
	if (a->errno == ERRNO_NONE)
		return ;
	display(a);
	if (a->fd[STDERR__] != STDERR__)
		exit(a->errno);
	a->rtn = a->errno;
	a->errno = 0;
	a->errarg = NULL;
}

static void	display(t_a *a)
{
	t_i8	err;

	err = STDERR__;
	write(a->fd[STDERR__], a->proc, a->proc_l);
	if (a->errarg)
	{
		write(a->fd[STDERR__], a->errarg, ft_strlen(a->errarg));
		write(a->fd[STDERR__], ": ", 2);
	}
	write(a->fd[STDERR__], a->errmsg[a->errno],
			ft_strlen(a->errmsg[a->errno]));
	write(a->fd[STDERR__], "\n", 1);
	write(a->fd[STDERR__], &err, 1);
}
