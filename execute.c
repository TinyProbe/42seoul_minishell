/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:20 by tkong             #+#    #+#             */
/*   Updated: 2023/01/21 19:44:02 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_db *db);
static void	setrange(t_db *db);
static void	extract(t_db *db);

void	execute(t_db *db)
{
	while (db->arg_begin < db->tkn_len)
	{
		init(db);
		setrange(db);
		extract(db);
		if ((db->conj == CONJ_ANDAND && db->rtn)
				|| (db->conj == CONJ_OROR && !(db->rtn)))
			continue ;
		process(db);
	}
}

static void	init(t_db *db)
{
	db->ac = 0;
	db->rein_len = 0;
	db->reout_len = 0;
	db->conj = CONJ_NONE;
}

static void	setrange(t_db *db)
{
	while (db->arg_end < db->tkn_len)
	{
		if (db->arg_begin != db->arg_end
				&& (db->tkn[db->arg_end][0] == '|'
					|| db->tkn[db->arg_end][0] == '&'))
			break ;
		db->arg_end++;
	}
}

static void	extract(t_db *db)
{
	while (db->arg_begin < db->arg_end)
	{
		substi(db);
		if (db->tkn[db->arg_begin][0] == '<' || db->rein_len & 1)
			db->rein[db->rein_len++] = db->tkn[db->arg_begin];
		else if (db->tkn[db->arg_begin][0] == '>' || db->reout_len & 1)
			db->reout[db->reout_len++] = db->tkn[db->arg_begin];
		else if (db->tkn[db->arg_begin][0] == '|')
			db->conj = CONJ_OR + (ft_strlen(db->tkn[db->arg_begin]) == 2);
		else if (db->tkn[db->arg_begin][0] == '&')
			db->conj = CONJ_ANDAND;
		else
			db->av[db->ac++] = db->tkn[db->arg_begin];
		db->arg_begin++;
	}
}
