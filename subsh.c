/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:02:01 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 13:53:41 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_a *a);

void	subsh(t_a *a)
{
	init(a);
	check(a);
	token(a);
	valid(a);
	execute(a);
}

static void	init(t_a *a)
{
	untoken(a);
	unrepl(a);
	a->ac = 0;
	a->ab = 0;
	a->ae = 0;
	a->ri_l = 0;
	a->ro_l = 0;
	a->conj = CONJ_NONE;
}
