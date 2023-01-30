/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:20 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 13:49:17 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_a *a);
static void	setrange(t_a *a);
static void	extract(t_a *a);

void	execute(t_a *a)
{
	while (a->ab < a->tkn_l)
	{
		init(a);
		setrange(a);
		extract(a);
		if ((a->conj == CONJ_ANDAND && a->rtn)
				|| (a->conj == CONJ_OROR && !(a->rtn)))
			continue ;
		a->cmd_l = 0;
		process(a);
	}
}

static void	init(t_a *a)
{
	a->ac = 0;
	a->ri_l = 0;
	a->ro_l = 0;
	a->conj = CONJ_NONE;
}

static void	setrange(t_a *a)
{
	while (a->ae < a->tkn_l)
	{
		if (a->ab != a->ae && (a->tkn[a->ae]._[0] == '|'
					|| a->tkn[a->ae]._[0] == '&'))
			break ;
		a->ae++;
	}
}

static void	extract(t_a *a)
{
	while (a->ab < a->ae)
	{
		subst(a);
		if (a->tkn[a->ab]._[0] == '<' || a->ri_l & 1)
			a->ri[a->ri_l++] = a->tkn[a->ab]._;
		else if (a->tkn[a->ab]._[0] == '>' || a->ro_l & 1)
			a->ro[a->ro_l++] = a->tkn[a->ab]._;
		else if (a->tkn[a->ab]._[0] == '|')
			a->conj = CONJ_OR + (a->tkn[a->ab].len == 2);
		else if (a->tkn[a->ab]._[0] == '&')
			a->conj = CONJ_ANDAND;
		else
			a->av[a->ac++] = a->tkn[a->ab]._;
		a->ab++;
	}
}
