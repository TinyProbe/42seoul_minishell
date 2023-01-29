/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:10:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 17:49:11 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	conjunct_deadline(t_z *z);
static void	conjunct_format(t_z *z, t_i32 i);
static void	conjunct_match(t_z *z, t_i32 i);
static void	redirect_match(t_z *z, t_i32 i);

void	valid(t_z *z)
{
	t_i32	i;

	i = -1;
	if (z->tkn_len)
		conjunct_deadline(z);
	while (++i < z->tkn_len)
	{
		conjunct_format(z, i);
		conjunct_match(z, i);
		redirect_match(z, i);
	}
}

static void	conjunct_deadline(t_z *z)
{
	if (z->tkn[0]._[0] == '|'
			|| z->tkn[0]._[0] == '&'
			|| z->tkn[0]._[0] == ';')
		z->errarg = z->tkn[0]._;
	else if (z->tkn[z->tkn_len - 1]._[0] == '|'
			|| z->tkn[z->tkn_len - 1]._[0] == '&'
			|| z->tkn[z->tkn_len - 1]._[0] == ';')
		z->errarg = z->tkn[z->tkn_len - 1]._;
	if (z->errarg)
		z->errno = ERRNO_FORMAT;
	error(z);
}

static void	conjunct_format(t_z *z, t_i32 i)
{
	if (z->tkn[i]._[0] == '|' && z->tkn[i].len > 2)
		z->errno = ERRNO_FORMAT;
	else if (z->tkn[i]._[0] == '&' || z->tkn[i]._[0] == ';')
	{
		if (z->tkn[i].len == 1)
			z->errno = ERRNO_RESTRICT;
		else if (z->tkn[i].len > 1 + (z->tkn[i]._[0] == '&'))
			z->errno = ERRNO_FORMAT;
	}
	if (z->errno)
		z->errarg = z->tkn[i]._;
	error(z);
}

static void	conjunct_match(t_z *z, t_i32 i)
{
	if (z->tkn[i]._[0] == '|'
			|| z->tkn[i]._[0] == '&'
			|| z->tkn[i]._[0] == ';')
	{
		if (i < z->tkn_len - 1 && (z->tkn[i + 1]._[0] == '|'
					|| z->tkn[i + 1]._[0] == '&'
					|| z->tkn[i + 1]._[0] == ';'))
		{
			z->errno = ERRNO_FORMAT;
			z->errarg = z->tkn[i + 1]._;
		}
	}
	error(z);
}

static void	redirect_match(t_z *z, t_i32 i)
{
	if (z->tkn[i]._[0] == '<' || z->tkn[i]._[0] == '>')
	{
		if (!(i < z->tkn_len - 1)
				|| (z->tkn[i + 1]._[0] == '|' || z->tkn[i + 1]._[0] == '&'
					|| z->tkn[i + 1]._[0] == ';' || z->tkn[i + 1]._[0] == '<'
					|| z->tkn[i + 1]._[0] == '>' || z->tkn[i + 1]._[0] == '('))
		{
			z->errno = ERRNO_FORMAT;
			z->errarg = z->tkn[i + (i < z->tkn_len - 1)]._;
		}
	}
	error(z);
}
