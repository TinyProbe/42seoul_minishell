/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_rp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:57:21 by tkong             #+#    #+#             */
/*   Updated: 2023/02/05 17:30:29 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	newlen(t_a *a);
static void		tkncpy(t_a *a, t_i8 *tkn);

void	apply_rp(t_a *a)
{
	t_i8	*tkn;
	t_i32	len;

	if (a->rp_l == 0)
		return ;
	len = newlen(a);
	tkn = (t_i8 *) malloc(sizeof(t_i8) * len + 1);
	tkncpy(a, tkn);
	free(a->tkn[a->ab]._);
	a->tkn[a->ab]._ = tkn;
	a->tkn[a->ab].len = len;
	unrepl(a);
}

static t_i32	newlen(t_a *a)
{
	t_i32	len;
	t_i32	i;

	len = a->tkn[a->ab].len;
	i = -1;
	while (++i < a->rp_l)
		len += (a->rp[i].len - (a->rp[i].r - a->rp[i].l));
	return (len);
}

static void	tkncpy(t_a *a, t_i8 *tkn)
{
	t_i32	i;
	t_i32	j;
	t_i32	k;
	t_i32	l;

	i = -1;
	j = 0;
	l = 0;
	while (++i < a->tkn[a->ab].len)
	{
		if (j < a->rp_l && i == a->rp[j].l)
		{
			k = -1;
			while (++k < a->rp[j].len)
				tkn[l++] = a->rp[j]._[k];
			i = a->rp[j++].r - 1;
		}
		else
			tkn[l++] = a->tkn[a->ab]._[i];
	}
	tkn[l] = '\0';
}
