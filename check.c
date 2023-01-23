/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:54:12 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 03:32:25 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	check(t_db *db)
{
	t_i32	i;

	i = -1;
	while (++i < db->len)
	{
		if (db->cmd[i] == '(' || db->cmd[i] == ')')
			bracket(db, db->cmd, i);
		else if (db->cmd[i] == '\'')
			quote(db);
		else if (db->cmd[i] == '"')
			claw(db);
		else if (db->cmd[i] == '\\')
			db->errno = ERRNO_RESTRICT;
		if (db->errno)
			error(db);
	}
	if (db->stk_len)
		db->errno = ERRNO_FORMAT;
	error(db);
}

void	bracket(t_db *db, t_i8 *s, t_i32 i)
{
	if (db->stk_len && db->stk[db->stk_len - 1] == '\'')
		return ;
	if (s[i] == '(')
	{
		if ((i > 0 && s[i - 1] == '$')
				|| (!(db->stk_len) || db->stk[db->stk_len - 1] == '('))
			db->stk[db->stk_len++] = '(';
	}
	else
	{
		if (db->stk_len && db->stk[db->stk_len - 1] == '(')
			db->stk_len--;
		else if (!(db->stk_len))
			db->errno = ERRNO_FORMAT;
	}
}

void	quote(t_db *db)
{
	if (db->stk_len && db->stk[db->stk_len - 1] == '"')
		return ;
	if (db->stk_len && db->stk[db->stk_len - 1] == '\'')
		db->stk_len--;
	else
		db->stk[db->stk_len++] = '\'';
}

void	claw(t_db *db)
{
	if (db->stk_len && db->stk[db->stk_len - 1] == '\'')
		return ;
	if (db->stk_len && db->stk[db->stk_len - 1] == '"')
		db->stk_len--;
	else
		db->stk[db->stk_len++] = '"';
}
