/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:16:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 14:37:58 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	recwd(t_z *z)
{
	if (!getcwd(z->cwd, CWD_MAX))
		z->errno = ERRNO_LONGCWD;
	else
		z->cwd_len = ft_strlen(z->cwd);
	error(z);
}

void	output(t_z *z, t_i32 out, t_i32 err)
{
	t_i32	i;
	t_i32	j;

	i = -1;
	j = 0;
	while (++i < z->buf_len)
	{
		if (z->buf[i] == STDOUT__)
		{
			write(out, z->buf + j, i - j + (out != STDOUT__));
			j = i + 1;
		}
		else if (z->buf[i] == STDERR__)
		{
			write(err, z->buf + j, i - j + (err != STDERR__));
			j = i + 1;
		}
	}
	z->buf_len = 0;
}

void	untoken(t_z *z)
{
	while (z->tkn_len--)
		free(z->tkn[z->tkn_len]._);
	z->tkn_len++;
}

void	unrepl(t_z *z)
{
	while (z->repl_len--)
		if (z->repl[z->repl_len].type != TYPE_ENV)
			free(z->repl[z->repl_len]._);
	z->repl_len++;
}
