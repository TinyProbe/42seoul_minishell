/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:20 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 07:00:13 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_db *db);
static void	setrange(t_db *db);
static void	extract(t_db *db);

void	execute(t_db *db)
{
	while (db->arg_b < db->tkn_len)
	{
		init(db);
		setrange(db);
		extract(db);
		if ((db->conj == CONJ_ANDAND && db->rtn)
				|| (db->conj == CONJ_OROR && !(db->rtn)))
			continue ;
		db->len = 0;
		process(db);
	}
}

static void	init(t_db *db)
{
	db->ac = 0;
	db->ri_len = 0;
	db->ro_len = 0;
	db->conj = CONJ_NONE;
}

static void	setrange(t_db *db)
{
	while (db->arg_e < db->tkn_len)
	{
		if (db->arg_b != db->arg_e
				&& (db->tkn[db->arg_e]._[0] == '|'
					|| db->tkn[db->arg_e]._[0] == '&'))
			break ;
		db->arg_e++;
	}
}

static void	extract(t_db *db)
{
	while (db->arg_b < db->arg_e)
	{
		substitution(db);
		if (db->tkn[db->arg_b]._[0] == '<' || db->ri_len & 1)
			db->ri[db->ri_len++] = db->tkn[db->arg_b]._;
		else if (db->tkn[db->arg_b]._[0] == '>' || db->ro_len & 1)
			db->ro[db->ro_len++] = db->tkn[db->arg_b]._;
		else if (db->tkn[db->arg_b]._[0] == '|')
			db->conj = CONJ_OR + (db->tkn[db->arg_b].len == 2);
		else if (db->tkn[db->arg_b]._[0] == '&')
			db->conj = CONJ_ANDAND;
		else
			db->av[db->ac++] = db->tkn[db->arg_b]._;
		db->arg_b++;
	}
}
