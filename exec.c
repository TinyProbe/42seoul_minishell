/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:20 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 02:37:05 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void		init(t_a *a);
static void		setrange(t_a *a);
static t_i32	extract(t_a *a);

t_i32	exec(t_a *a)
{
	while (a->ab < a->tkn_l)
	{
		init(a);
		setrange(a);
		if (extract(a))
			break ;
		if ((a->conj == CONJ_ANDAND && a->rtn)
			|| (a->conj == CONJ_OROR && !(a->rtn)))
			continue ;
		a->cmd_l = 0;
		re_(a);
		(void) (self(a) && process(a));
	}
	return (a->errn);
}

static void	init(t_a *a)
{
	unext(a);
	a->ac = 0;
	a->ri_l = 0;
	a->ro_l = 0;
	a->conj = CONJ_NONE;
	a->dup2_cnt = a->dup2_cnt_old;
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
	if (a->ab != a->ae && (a->ae < a->tkn_l && a->tkn[a->ae]._[0] == '|'))
		a->dup2_cnt++;
}

static t_i32	extract(t_a *a)
{
	while (a->ab < a->ae)
	{
		if (subst(a))
			return (a->errn);
		if (a->tkn[a->ab]._ == NULL)
			;
		else if (a->tkn[a->ab]._[0] == '<' || a->ri_l & 1)
			a->ri[a->ri_l++] = a->tkn[a->ab]._;
		else if (a->tkn[a->ab]._[0] == '>' || a->ro_l & 1)
		{
			a->ro[a->ro_l++] = a->tkn[a->ab]._;
			a->dup2_cnt++;
		}
		else if (a->tkn[a->ab]._[0] == '|')
			a->conj = CONJ_OR + (a->tkn[a->ab].len == 2);
		else if (a->tkn[a->ab]._[0] == '&')
			a->conj = CONJ_ANDAND;
		else
			a->av[a->ac++] = a->tkn[a->ab]._;
		a->ab++;
	}
	a->av[a->ac] = NULL;
	return (a->errn);
}
