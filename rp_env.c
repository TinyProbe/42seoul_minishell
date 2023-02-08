/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rp_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:01:19 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 17:26:13 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_a *a);

void	rp_env(t_a *a)
{
	t_i32	n;
	t_i8	*tmp;

	if (a->tkn[a->ab]._[a->rp[a->rp_l].l + 1] == '?')
	{
		a->rp[a->rp_l]._ = ft_itoa(a->rtn);
		a->rp[a->rp_l].type = TYPE_ENV_RTN;
	}
	else
	{
		n = a->rp[a->rp_l].r - a->rp[a->rp_l].l - 1;
		tmp = ft_strndup(a->tkn[a->ab]._ + a->rp[a->rp_l].l + 1, n);
		a->rp[a->rp_l]._ = getenv__(a, tmp);
		free(tmp);
		if (a->rp[a->rp_l]._ == NULL)
			a->rp[a->rp_l]._ = "\0";
		a->rp[a->rp_l].type = TYPE_ENV;
	}
	a->rp[a->rp_l].len = ft_strlen(a->rp[a->rp_l]._);
	init(a);
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
