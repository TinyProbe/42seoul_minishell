/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:57:21 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 14:43:57 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	newlen(t_z *z);
static void		tkncpy(t_z *z, t_i8 *tkn, t_i32 len);

void	apply_repl(t_z *z)
{
	t_i8	*tkn;
	t_i32	len;

	if (z->repl_len == 0)
		return ;
	len = newlen(z);
	tkn = (t_i8 *) malloc(sizeof(t_i8) * len + 1);
	tkncpy(z, tkn, len);
	free(z->tkn[z->ab]._);
	z->tkn[z->ab]._ = tkn;
	z->tkn[z->ab].len = len;
}

static t_i32	newlen(t_z *z)
{
	t_i32	len;
	t_i32	i;

	len = z->tkn[z->ab].len;
	i = -1;
	while (++i < z->repl_len)
		len += (z->repl[i].len - (z->repl[i].r - z->repl[i].l));
	return (len);
}

static void		tkncpy(t_z *z, t_i8 *tkn, t_i32 len)
{
	t_i32	i[4];

	i[0] = -1;
	i[1] = 0;
	i[2] = 0;
	while (++i[0] < len)
	{
		tkn[i[0]] = z->tkn[z->ab]._[i[1]++];
		if (i[1] == z->repl[i[2]].l)
		{
			i[3] = -1;
			while (++i[3] < z->repl[i[2]].len)
				tkn[++i[0]] = z->repl[i[2]]._[i[3]];
			i[1] = z->repl[i[2]++].r;
		}
	}
	tkn[len] = '\0';
}
