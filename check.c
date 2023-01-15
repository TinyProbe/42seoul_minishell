/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:54:12 by tkong             #+#    #+#             */
/*   Updated: 2023/01/15 20:22:52 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_i32	check(t_db *db)
{
	t_i32	i;

	i = -1;
	while (++i < db->len)
		if (db->cmd[i] == '(' || db->cmd[i] == ')')
			bracket(db, i);
		else if (db->cmd[i] == '\'')
			quote(db);
		else if (db->cmd[i] == '"')
			claw(db);
		else if (db->cmd[i] == '\\')
			db->errno = ERRNO_RESTRICT;
	if (!(db->errno) && db->stk_len)
		db->errno = ERRNO_FORMAT;
	if (db->errno)
		return (-1);
	return (0);
}

void	bracket(t_db *db, t_i32 i)
{
	if (db->stk_len && db->stk[db->stk_len - 1] == '\'')
		return ;
	if (db->cmd[i] == '(')
	{
		if ((i > 0 && db->cmd[i - 1] == '$')
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
