/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:16:05 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 05:00:30 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	recwd(t_a *a)
{
	if (!getcwd(a->cwd, CWD_MAX))
		a->errn = ERR_LONGCWD;
	else
		a->cwd_l = ft_strlen(a->cwd);
	error(a);
}

void	output(t_a *a, t_i32 out, t_i32 err)
{
	t_i32	i;
	t_i32	j;

	i = -1;
	j = 0;
	a->lln_l = 0;
	while (++i < a->buf_l)
	{
		if (a->buf[i] == STDOUT__)
		{
			write(out, a->buf + j, i - j + cmdtype(a));
			j = i + 1;
		}
		else if (a->buf[i] == STDERR__)
		{
			write(err, a->buf + j, i - j + (err != STDERR__));
			j = i + 1;
		}
	}
	if (i != j)
		write(out, a->buf + j, i - j);
	if (out == STDOUT__)
		lastln(a);
	a->buf_l = 0;
}

void	endout(t_a *a, t_i8 fd)
{
	write(a->fd[(t_i32) fd], &fd, 1);
}

void	untoken(t_a *a)
{
	while (a->tkn_l--)
		free(a->tkn[a->tkn_l]._);
	a->tkn_l++;
}

void	unrepl(t_a *a)
{
	while (a->rp_l--)
		if (a->rp[a->rp_l].type != TYPE_ENV)
			free(a->rp[a->rp_l]._);
	a->rp_l++;
}
