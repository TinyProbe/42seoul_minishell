/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:20 by tkong             #+#    #+#             */
/*   Updated: 2023/01/19 20:22:08 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	argumentation(t_db *db, t_i32 i);
static void		init(t_db *db);

t_i32	execute(t_db *db)
{
	t_i32	i;

	i = -1;
	while (++i < db->tkn_len)
	{
		i = argumentation(db, i);
		if ((db->ctrl == CTRL_ANDAND && db->rtn)
				|| (db->ctrl == CTRL_OROR && !(db->rtn)))
			continue ;
		process(db);
	}
	return (0);
}

static t_i32	argumentation(t_db *db, t_i32 i)
{
	init(db);
	while (++i < db->tkn_len)
		if (apply(db, i))
			break ;
	return i - 1;
}

static void	init(t_db *db)
{
	db->ftr = NULL;
	db->ac = 0;
	db->opt = NULL;
	db->rein_len = 0;
	db->reout_len = 0;
	db->ctrl = CTRL_NONE;
}
