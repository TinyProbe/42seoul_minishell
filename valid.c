/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:10:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/21 00:16:12 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	conjunct_deadline(t_db *db);
static t_i32	conjunct_format(t_db *db, t_i32 i);
static t_i32	conjunct_match(t_db *db, t_i32 i);
static t_i32	redirect_match(t_db *db, t_i32 i);

t_i32	valid(t_db *db)
{
	t_i32	i;

	i = -1;
	if (conjunct_deadline(db))
		return (-1);
	while (++i < db->tkn_len)
		if (conjunct_format(db, i)
				|| conjunct_match(db, i)
				|| redirect_match(db, i))
			return (-1);
	return (0);
}

static t_i32	conjunct_deadline(t_db *db)
{
	if (db->tkn[0][0] == '|'
			|| db->tkn[0][0] == '&'
			|| db->tkn[0][0] == ';')
		db->errarg = db->tkn[0];
	else if (db->tkn[db->tkn_len - 1][0] == '|'
			|| db->tkn[db->tkn_len - 1][0] == '&'
			|| db->tkn[db->tkn_len - 1][0] == ';')
		db->errarg = db->tkn[db->tkn_len - 1];
	if (db->errarg)
	{
		db->errno = ERRNO_FORMAT;
		return (-1);
	}
	return (0);
}

static t_i32	conjunct_format(t_db *db, t_i32 i)
{
	if (db->tkn[i][0] == '|' && ft_strlen(db->tkn[i]) > 2)
		db->errno = ERRNO_FORMAT;
	else if (db->tkn[i][0] == '&' || db->tkn[i][0] == ';')
	{
		if (ft_strlen(db->tkn[i]) == 1)
			db->errno = ERRNO_RESTRICT;
		else if (ft_strlen(db->tkn[i]) > 1 + (db->tkn[i][0] == '&'))
			db->errno = ERRNO_FORMAT;
	}
	if (db->errno)
	{
		db->errarg = db->tkn[i];
		return (-1);
	}
	return (0);
}

static t_i32	conjunct_match(t_db *db, t_i32 i)
{
	if (db->tkn[i][0] == '|' || db->tkn[i][0] == '&' || db->tkn[i][0] == ';')
		if (i < db->tkn_len - 1 && (db->tkn[i + 1][0] == '|'
					|| db->tkn[i + 1][0] == '&'
					|| db->tkn[i + 1][0] == ';'))
		{
			db->errno = ERRNO_FORMAT;
			db->errarg = db->tkn[i + 1];
			return (-1);
		}
	return (0);
}

static t_i32	redirect_match(t_db *db, t_i32 i)
{
	if (db->tkn[i][0] == '<' || db->tkn[i][0] == '>')
		if (!(i < db->tkn_len - 1) || (db->tkn[i + 1][0] == '|'
					|| db->tkn[i + 1][0] == '&'
					|| db->tkn[i + 1][0] == ';'
					|| db->tkn[i + 1][0] == '<'
					|| db->tkn[i + 1][0] == '>'
					|| db->tkn[i + 1][0] == '('))
		{
			db->errno = ERRNO_FORMAT;
			db->errarg = db->tkn[i + (i < db->tkn_len - 1)];
			return (-1);
		}
	return (0);
}
