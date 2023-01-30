/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:20 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 11:15:01 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_z *z);
static void	setrange(t_z *z);
static void	extract(t_z *z);

void	execute(t_z *z)
{
	while (z->ab < z->tkn_len)
	{
		init(z);
		setrange(z);
		extract(z);
		if ((z->conj == CONJ_ANDAND && z->rtn)
				|| (z->conj == CONJ_OROR && !(z->rtn)))
			continue ;
		z->len = 0;
		process(z);
	}
}

static void	init(t_z *z)
{
	z->ac = 0;
	z->ri_len = 0;
	z->ro_len = 0;
	z->conj = CONJ_NONE;
}

static void	setrange(t_z *z)
{
	while (z->ae < z->tkn_len)
	{
		if (z->ab != z->ae && (z->tkn[z->ae]._[0] == '|'
					|| z->tkn[z->ae]._[0] == '&'))
			break ;
		z->ae++;
	}
}

static void	extract(t_z *z)
{
	while (z->ab < z->ae)
	{
		subst(z);
		if (z->tkn[z->ab]._[0] == '<' || z->ri_len & 1)
			z->ri[z->ri_len++] = z->tkn[z->ab]._;
		else if (z->tkn[z->ab]._[0] == '>' || z->ro_len & 1)
			z->ro[z->ro_len++] = z->tkn[z->ab]._;
		else if (z->tkn[z->ab]._[0] == '|')
			z->conj = CONJ_OR + (z->tkn[z->ab].len == 2);
		else if (z->tkn[z->ab]._[0] == '&')
			z->conj = CONJ_ANDAND;
		else
			z->av[z->ac++] = z->tkn[z->ab]._;
		z->ab++;
	}
}
