/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 05:29:50 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 07:01:11 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	variable(t_db *db);
static void	check_stack(t_db *db);
static void	setrange(t_db *db);
static void	wildcard(t_db *db);

void	substitution(t_db *db)
{
	db->repl[db->repl_len].l = -1;
	db->repl[db->repl_len].r = -1;
	db->repl[db->repl_len].last = -1;
	db->repl[db->repl_len].type = TYPE_NONE;
	db->repl[db->repl_len]._ = NULL;
	db->repl[db->repl_len].len = 0;
	variable(db);
	wildcard(db);
}

static void	variable(t_db *db)
{
	while (++(db->repl[db->repl_len].r) < db->len)
	{
		if (db->tkn[db->arg_b]._[db->repl[db->repl_len].r] == '('
				|| db->tkn[db->arg_b]._[db->repl[db->repl_len].r] == ')')
			bracket(db, db->tkn[db->arg_b]._, db->repl[db->repl_len].r);
		else if (db->tkn[db->arg_b]._[db->repl[db->repl_len].r] == '\'')
			quote(db);
		else if (db->tkn[db->arg_b]._[db->repl[db->repl_len].r] == '"')
			claw(db);
		check_stack(db);
	}
	apply_repl(db);
}

static void	check_stack(t_db *db)
{
	if (db->stk_len > 1 || (db->stk_len && db->stk[db->stk_len - 1] != '"'))
		return ;
	if (db->repl[db->repl_len].r < db->tkn[db->arg_b].len - 1
			&& db->tkn[db->arg_b]._[db->repl[db->repl_len].r] == '$')
	{
		if (db->tkn[db->arg_b]._[db->repl[db->repl_len].r + 1] == '(')
		{
			db->repl[db->repl_len].l = db->repl[db->repl_len].r;
			db->repl[db->repl_len].last = db->stk_len;
		}
		else
		{
			setrange(db);
			repl_env(db);
		}
	}
	else if (db->stk_len == db->repl[db->repl_len].last
			&& db->tkn[db->arg_b]._[db->repl[db->repl_len].r] == ')')
	{
		db->repl[db->repl_len].r++;
		repl_cmd(db);
	}
}

static void	setrange(t_db *db)
{
	db->repl[db->repl_len].l = db->repl[db->repl_len].r;
	if (ft_isdigit(db->tkn[db->arg_b]._[db->repl[db->repl_len].r + 1])
			|| db->tkn[db->arg_b]._[db->repl[db->repl_len].r + 1] == '?')
	{
		db->repl[db->repl_len].r += 2;
		return ;
	}
	while (++(db->repl[db->repl_len].r) < db->tkn[db->arg_b].len)
		if (db->tkn[db->arg_b]._[db->repl[db->repl_len].r] != '_'
				&& !ft_isalnum(db->tkn[db->arg_b]._[db->repl[db->repl_len].r]))
			break ;
}

static void	wildcard(t_db *db)
{
	t_i32	i;

	i = -1;
	if (db->buf[0] == '(')
		return ;
	while (++i < db->tkn[db->arg_b].len)
	{
		if (db->tkn[db->arg_b]._[i] == '(' || db->tkn[db->arg_b]._[i] == ')')
			bracket(db, db->tkn[db->arg_b]._, i);
		else if (db->tkn[db->arg_b]._[i] == '\'')
			quote(db);
		else if (db->tkn[db->arg_b]._[i] == '"')
			claw(db);
		if (db->tkn[db->arg_b]._[i] == '*' && db->stk_len)
		{
			db->tkn[db->arg_b].len = ft_strdel(db->tkn[db->arg_b]._, "'\"");
			return ;
		}
	}
	db->tkn[db->arg_b].len = ft_strdel(db->tkn[db->arg_b]._, "'\"");
	repl_wild(db);
}
