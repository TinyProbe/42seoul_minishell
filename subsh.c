/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:02:01 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 10:40:30 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_z *z);

void	subsh(t_z *z)
{
	init(z);
	check(z);
	token(z);
	valid(z);
	execute(z);
}

static void	init(t_z *z)
{
	untoken(z);
	unrepl(z);
	z->ac = 0;
	z->ab = 0;
	z->ae = 0;
	z->ri_len = 0;
	z->ro_len = 0;
	z->conj = CONJ_NONE;
}
