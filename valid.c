/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:10:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 06:22:54 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	conjunct_deadline(t_db *db);
static void	conjunct_format(t_db *db, t_i32 i);
static void	conjunct_match(t_db *db, t_i32 i);
static void	redirect_match(t_db *db, t_i32 i);

void	valid(t_db *db)
{
	t_i32	i;

	i = -1;
	conjunct_deadline(db);
	while (++i < db->tkn_len)
	{
		conjunct_format(db, i);
		conjunct_match(db, i);
		redirect_match(db, i);
	}
}

static void	conjunct_deadline(t_db *db)
{
	if (db->tkn[0]._[0] == '|'
			|| db->tkn[0]._[0] == '&'
			|| db->tkn[0]._[0] == ';')
		db->errarg = db->tkn[0]._;
	else if (db->tkn[db->tkn_len - 1]._[0] == '|'
			|| db->tkn[db->tkn_len - 1]._[0] == '&'
			|| db->tkn[db->tkn_len - 1]._[0] == ';')
		db->errarg = db->tkn[db->tkn_len - 1]._;
	if (db->errarg)
		db->errno = ERRNO_FORMAT;
	error(db);
}

static void	conjunct_format(t_db *db, t_i32 i)
{
	if (db->tkn[i]._[0] == '|' && db->tkn[i].len > 2)
		db->errno = ERRNO_FORMAT;
	else if (db->tkn[i]._[0] == '&' || db->tkn[i]._[0] == ';')
	{
		if (db->tkn[i].len == 1)
			db->errno = ERRNO_RESTRICT;
		else if (db->tkn[i].len > 1 + (db->tkn[i]._[0] == '&'))
			db->errno = ERRNO_FORMAT;
	}
	if (db->errno)
		db->errarg = db->tkn[i]._;
	error(db);
}

static void	conjunct_match(t_db *db, t_i32 i)
{
	if (db->tkn[i]._[0] == '|'
			|| db->tkn[i]._[0] == '&'
			|| db->tkn[i]._[0] == ';')
	{
		if (i < db->tkn_len - 1 && (db->tkn[i + 1]._[0] == '|'
					|| db->tkn[i + 1]._[0] == '&'
					|| db->tkn[i + 1]._[0] == ';'))
		{
			db->errno = ERRNO_FORMAT;
			db->errarg = db->tkn[i + 1]._;
		}
	}
	error(db);
}

static void	redirect_match(t_db *db, t_i32 i)
{
	if (db->tkn[i]._[0] == '<' || db->tkn[i]._[0] == '>')
	{
		if (!(i < db->tkn_len - 1)
				|| (db->tkn[i + 1]._[0] == '|' || db->tkn[i + 1]._[0] == '&'
					|| db->tkn[i + 1]._[0] == ';' || db->tkn[i + 1]._[0] == '<'
					|| db->tkn[i + 1]._[0] == '>' || db->tkn[i + 1]._[0] == '('))
		{
			db->errno = ERRNO_FORMAT;
			db->errarg = db->tkn[i + (i < db->tkn_len - 1)]._;
		}
	}
	error(db);
}
