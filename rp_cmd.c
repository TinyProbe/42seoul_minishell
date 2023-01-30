/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:33:56 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 13:58:35 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	rp_buf(t_a *a);
static void	init(t_a *a);

void	rp_cmd(t_a *a)
{
	a->cmd_l = a->rp[a->rp_l].r - a->rp[a->rp_l].l - 3;
	ft_memcpy(a->cmd, a->tkn[a->ab]._ + a->rp[a->rp_l].l + 2, a->cmd_l);
	process(a);
	rp_buf(a);
	a->rp[a->rp_l]._ = ft_memcpy(
			malloc(sizeof(t_i8) * a->buf_l + 1), a->buf, a->buf_l);
	a->rp[a->rp_l]._[a->buf_l] = '\0';
	a->rp[a->rp_l].len = a->buf_l;
	a->rp[a->rp_l].type = TYPE_CMD;
	init(a);
}

static void	rp_buf(t_a *a)
{
	t_i32	i;
	t_i32	j;
	t_i32	k;

	i = -1;
	j = 0;
	k = 0;
	while (++i < a->buf_l)
	{
		if (a->buf[i] == STDOUT__)
		{
			while (j < i)
				a->buf[k++] = a->buf[j++];
			j = i + 1;
		}
		else if (a->buf[i] == STDERR__)
		{
			write(a->fd[STDERR__], a->buf + j, i - j + 1);
			j = i + 1;
		}
	}
	a->buf_l = k;
}

static void	init(t_a *a)
{
	a->rp_l++;
	a->rp[a->rp_l].l = a->rp[a->rp_l - 1].l;
	a->rp[a->rp_l].r = a->rp[a->rp_l - 1].r;
	a->rp[a->rp_l].last = -1;
	a->rp[a->rp_l].type = TYPE_NONE;
	a->rp[a->rp_l]._ = NULL;
	a->rp[a->rp_l].len = 0;
}
