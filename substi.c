/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 05:29:50 by tkong             #+#    #+#             */
/*   Updated: 2023/01/22 01:15:26 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	variable(t_db *db);
static void	stack_check(t_db *db);
static void	setrange(t_db *db);
static void	wildcard(t_db *db);

void	substi(t_db *db)
{
	db->len = ft_strcpy(db->cmd, db->tkn[db->arg_begin]);
	db->tool[db->tool_len].l = -1;
	db->tool[db->tool_len].r = -1;
	db->tool[db->tool_len].last = -1;
	db->tool[db->tool_len].res = NULL;
	db->tool[db->tool_len].len = 0;
	variable(db);
	wildcard(db);
	db->tool_len++;
}

static void	variable(t_db *db)
{
	while (++(db->tool[db->tool_len].r) < db->len)
	{
		if (db->cmd[db->tool[db->tool_len].r] == '('
				|| db->cmd[db->tool[db->tool_len].r] == ')')
			bracket(db, db->tool[db->tool_len].r);
		else if (db->cmd[db->tool[db->tool_len].r] == '\'')
			quote(db);
		else if (db->cmd[db->tool[db->tool_len].r] == '"')
			claw(db);
		stack_check(db);
	}
}

static void	stack_check(t_db *db)
{
	if (db->stk_len > 1 || (db->stk_len && db->stk[db->stk_len - 1] != '"'))
		return ;
	if (db->tool[db->tool_len].r < db->len - 1
			&& db->cmd[db->tool[db->tool_len].r] == '$')
	{
		if (db->cmd[db->tool[db->tool_len].r + 1] == '(')
		{
			db->tool[db->tool_len].l = db->tool[db->tool_len].r;
			db->tool[db->tool_len].last = db->stk_len;
		}
		else
		{
			setrange(db);
			repl_env(db);
		}
	}
	else if (db->stk_len == db->tool[db->tool_len].last
			&& db->cmd[db->tool[db->tool_len].r] == ')')
	{
		db->tool[db->tool_len].r++;
		repl_cmd(db);
	}
}

static void	setrange(t_db *db)
{
	db->tool[db->tool_len].l = db->tool[db->tool_len].r;
	if (ft_isdigit(db->cmd[db->tool[db->tool_len].r + 1])
			|| db->cmd[db->tool[db->tool_len].r + 1] == '?')
	{
		db->tool[db->tool_len].r += 2;
		return ;
	}
	while (++(db->tool[db->tool_len].r) < db->len)
		if (db->cmd[db->tool[db->tool_len].r] != '_'
				&& !ft_isalnum(db->cmd[db->tool[db->tool_len].r]))
			break ;
}

static void	wildcard(t_db *db)
{
	t_i32	i;

	i = -1;
	if (db->cmd[0] == '(')
		return ;
	while (++i < db->len)
	{
		if (db->cmd[i] == '(' || db->cmd[i] == ')')
			bracket(db, i);
		else if (db->cmd[i] == '\'')
			quote(db);
		else if (db->cmd[i] == '"')
			claw(db);
		if (db->cmd[i] == '*' && db->stk_len)
		{
			db->len = ft_strdel(db->cmd, "'\"");
			return ;
		}
	}
	db->len = ft_strdel(db->cmd, "'\"");
	repl_wild(db);
}
