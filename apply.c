/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:57:21 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 09:41:07 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	newlen(t_db *db);
static void		tkncpy(t_db *db, t_i8 *tkn, t_i32 len);

void	apply_repl(t_db *db)
{
	t_i8	*tkn;
	t_i32	len;

	if (db->repl_len == 0)
		return ;
	len = newlen(db);
	tkn = (t_i8 *) malloc(sizeof(t_i8) * len + 1);
	tkncpy(db, tkn, len);
	free(db->tkn[db->arg_b]._);
	db->tkn[db->arg_b]._ = tkn;
	db->tkn[db->arg_b].len = len;
}

static t_i32	newlen(t_db *db)
{
	t_i32	len;
	t_i32	i;

	len = db->tkn[db->arg_b].len;
	i = -1;
	while (++i < db->repl_len)
		len += (db->repl[i].len - (db->repl[i].r - db->repl[i].l));
	return (len);
}

static void		tkncpy(t_db *db, t_i8 *tkn, t_i32 len)
{
	t_i32	i[4];

	i[0] = -1;
	i[1] = 0;
	i[2] = 0;
	while (++i[0] < len)
	{
		tkn[i[0]] = db->tkn[db->arg_b]._[i[1]++];
		if (i[1] == db->repl[i[2]].l)
		{
			i[3] = -1;
			while (++i[3] < db->repl[i[2]].len)
				tkn[++i[0]] = db->repl[i[2]]._[i[3]];
			i[1] = db->repl[i[2]++].r;
		}
	}
	tkn[len] = '\0';
}
