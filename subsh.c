/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:02:01 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 06:29:56 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_db *db);

void	subsh(t_db *db)
{
	init(db);
	check(db);
	token(db);
	valid(db);
	execute(db);
}

static void	init(t_db *db)
{
	untoken(db);
	unrepl(db);
	db->ac = 0;
	db->arg_b = 0;
	db->arg_e = 0;
	db->ri_len = 0;
	db->ro_len = 0;
	db->conj = CONJ_NONE;
}
