/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:33 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 14:43:57 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	display(t_z *z);

void	error(t_z *z)
{
	if (z->errno == ERRNO_NONE)
		return ;
	display(z);
	if (z->fd[STDERR__] != STDERR__)
		exit(z->errno);
	z->rtn = z->errno;
	z->errno = 0;
	z->errarg = NULL;
}

static void	display(t_z *z)
{
	t_i8	err;

	err = STDERR__;
	write(z->fd[STDERR__], z->proc, z->proc_len);
	if (z->errarg)
	{
		write(z->fd[STDERR__], z->errarg, ft_strlen(z->errarg));
		write(z->fd[STDERR__], ": ", 2);
	}
	write(z->fd[STDERR__], z->errmsg[z->errno],
			ft_strlen(z->errmsg[z->errno]));
	write(z->fd[STDERR__], "\n", 1);
	write(z->fd[STDERR__], &err, 1);
}
