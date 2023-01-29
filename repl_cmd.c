/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:33:56 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 15:31:40 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	repl_buf(t_z *z);
static void	init(t_z *z);

void	repl_cmd(t_z *z)
{
	z->len = z->repl[z->repl_len].r - z->repl[z->repl_len].l - 3;
	ft_memcpy(z->cmd, z->tkn[z->ab]._ + z->repl[z->repl_len].l + 2, z->len);
	process(z);
	repl_buf(z);
	z->repl[z->repl_len]._ = ft_memcpy(
			malloc(sizeof(t_i8) * z->buf_len + 1), z->buf, z->buf_len);
	z->repl[z->repl_len]._[z->buf_len] = '\0';
	z->repl[z->repl_len].len = z->buf_len;
	z->repl[z->repl_len].type = TYPE_CMD;
	init(z);
}

static void	repl_buf(t_z *z)
{
	t_i32	i;
	t_i32	j;
	t_i32	k;

	i = -1;
	j = 0;
	k = 0;
	while (++i < z->buf_len)
	{
		if (z->buf[i] == STDOUT__)
		{
			while (j < i)
				z->buf[k++] = z->buf[j++];
			j = i + 1;
		}
		else if (z->buf[i] == STDERR__)
		{
			write(z->fd[STDERR__], z->buf + j, i - j + 1);
			j = i + 1;
		}
	}
	z->buf_len = k;
}

static void	init(t_z *z)
{
	z->repl_len++;
	z->repl[z->repl_len].l = z->repl[z->repl_len - 1].l;
	z->repl[z->repl_len].r = z->repl[z->repl_len - 1].r;
	z->repl[z->repl_len].last = -1;
	z->repl[z->repl_len].type = TYPE_NONE;
	z->repl[z->repl_len]._ = NULL;
	z->repl[z->repl_len].len = 0;
}
