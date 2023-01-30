/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:10:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 13:56:26 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	conjunct_deadline(t_a *a);
static void	conjunct_format(t_a *a, t_i32 i);
static void	conjunct_match(t_a *a, t_i32 i);
static void	redirect_match(t_a *a, t_i32 i);

void	valid(t_a *a)
{
	t_i32	i;

	i = -1;
	if (a->tkn_l)
		conjunct_deadline(a);
	while (++i < a->tkn_l)
	{
		conjunct_format(a, i);
		conjunct_match(a, i);
		redirect_match(a, i);
	}
}

static void	conjunct_deadline(t_a *a)
{
	if (a->tkn[0]._[0] == '|'
			|| a->tkn[0]._[0] == '&'
			|| a->tkn[0]._[0] == ';')
		a->errarg = a->tkn[0]._;
	else if (a->tkn[a->tkn_l - 1]._[0] == '|'
			|| a->tkn[a->tkn_l - 1]._[0] == '&'
			|| a->tkn[a->tkn_l - 1]._[0] == ';')
		a->errarg = a->tkn[a->tkn_l - 1]._;
	if (a->errarg)
		a->errno = ERRNO_FORMAT;
	error(a);
}

static void	conjunct_format(t_a *a, t_i32 i)
{
	if (a->tkn[i]._[0] == '|' && a->tkn[i].len > 2)
		a->errno = ERRNO_FORMAT;
	else if (a->tkn[i]._[0] == '&' || a->tkn[i]._[0] == ';')
	{
		if (a->tkn[i].len == 1)
			a->errno = ERRNO_RESTRICT;
		else if (a->tkn[i].len > 1 + (a->tkn[i]._[0] == '&'))
			a->errno = ERRNO_FORMAT;
	}
	if (a->errno)
		a->errarg = a->tkn[i]._;
	error(a);
}

static void	conjunct_match(t_a *a, t_i32 i)
{
	if (a->tkn[i]._[0] == '|'
			|| a->tkn[i]._[0] == '&'
			|| a->tkn[i]._[0] == ';')
	{
		if (i < a->tkn_l - 1 && (a->tkn[i + 1]._[0] == '|'
					|| a->tkn[i + 1]._[0] == '&'
					|| a->tkn[i + 1]._[0] == ';'))
		{
			a->errno = ERRNO_FORMAT;
			a->errarg = a->tkn[i + 1]._;
		}
	}
	error(a);
}

static void	redirect_match(t_a *a, t_i32 i)
{
	if (a->tkn[i]._[0] == '<' || a->tkn[i]._[0] == '>')
	{
		if (!(i < a->tkn_l - 1)
				|| (a->tkn[i + 1]._[0] == '|' || a->tkn[i + 1]._[0] == '&'
					|| a->tkn[i + 1]._[0] == ';' || a->tkn[i + 1]._[0] == '<'
					|| a->tkn[i + 1]._[0] == '>' || a->tkn[i + 1]._[0] == '('))
		{
			a->errno = ERRNO_FORMAT;
			a->errarg = a->tkn[i + (i < a->tkn_l - 1)]._;
		}
	}
	error(a);
}
