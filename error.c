/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:33 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 02:17:06 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	display(t_a *a);

void	error(t_a *a)
{
	if (a->errn == ERR_NONE)
		return ;
	display(a);
	if (a->fd[STDERR__] != STDERR__)
		exit(a->errn);
	a->rtn = a->errn;
	a->errn = 0;
	a->erra = NULL;
}

static void	display(t_a *a)
{
	write(a->fd[STDERR__], a->proc, a->proc_l);
	if (a->erra)
	{
		write(a->fd[STDERR__], a->erra, ft_strlen(a->erra));
		write(a->fd[STDERR__], ": ", 2);
	}
	write(a->fd[STDERR__], a->errm[a->errn], ft_strlen(a->errm[a->errn]));
	write(a->fd[STDERR__], "\n", 1);
	if (a->fd[STDERR__] != STDERR__)
		endout(a, STDERR__);
}
