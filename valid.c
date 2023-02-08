/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:10:05 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 15:16:39 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	conj_deadline(t_a *a);
static t_i32	conj_format(t_a *a, t_i32 i);
static t_i32	conj_match(t_a *a, t_i32 i);
static t_i32	redi_match(t_a *a, t_i32 i);

t_i32	valid(t_a *a)
{
	t_i32	i;

	i = -1;
	if (a->tkn_l)
		conj_deadline(a);
	while (++i < a->tkn_l)
		if (conj_format(a, i) || conj_match(a, i) || redi_match(a, i))
			break ;
	return (a->errn);
}

static t_i32	conj_deadline(t_a *a)
{
	if (a->tkn[0]._[0] == '|'
		|| a->tkn[0]._[0] == '&'
		|| a->tkn[0]._[0] == ';')
		a->erra = a->tkn[0]._;
	else if (a->tkn[a->tkn_l - 1]._[0] == '|'
		|| a->tkn[a->tkn_l - 1]._[0] == '&'
		|| a->tkn[a->tkn_l - 1]._[0] == ';')
		a->erra = a->tkn[a->tkn_l - 1]._;
	if (a->erra)
		a->errn = ERR_FORMAT;
	return (a->errn);
}

static t_i32	conj_format(t_a *a, t_i32 i)
{
	if (a->tkn[i]._[0] == '|' && a->tkn[i].len > 2)
		a->errn = ERR_FORMAT;
	else if (a->tkn[i]._[0] == '&' || a->tkn[i]._[0] == ';')
	{
		if (a->tkn[i].len == 1)
			a->errn = ERR_RESTRICT;
		else if (a->tkn[i].len > 1 + (a->tkn[i]._[0] == '&'))
			a->errn = ERR_FORMAT;
	}
	if (a->errn)
		a->erra = a->tkn[i]._;
	return (a->errn);
}

static t_i32	conj_match(t_a *a, t_i32 i)
{
	if (a->tkn[i]._[0] == '|'
		|| a->tkn[i]._[0] == '&'
		|| a->tkn[i]._[0] == ';')
	{
		if (i < a->tkn_l - 1 && (a->tkn[i + 1]._[0] == '|'
				|| a->tkn[i + 1]._[0] == '&'
				|| a->tkn[i + 1]._[0] == ';'))
		{
			a->errn = ERR_FORMAT;
			a->erra = a->tkn[i + 1]._;
		}
	}
	return (a->errn);
}

static t_i32	redi_match(t_a *a, t_i32 i)
{
	if (a->tkn[i]._[0] == '<' || a->tkn[i]._[0] == '>')
	{
		if (!(i < a->tkn_l - 1)
			|| (a->tkn[i + 1]._[0] == '|' || a->tkn[i + 1]._[0] == '&'
				|| a->tkn[i + 1]._[0] == ';' || a->tkn[i + 1]._[0] == '<'
				|| a->tkn[i + 1]._[0] == '>' || a->tkn[i + 1]._[0] == '('))
		{
			a->errn = ERR_FORMAT;
			a->erra = a->tkn[i + (i < a->tkn_l - 1)]._;
		}
	}
	return (a->errn);
}
