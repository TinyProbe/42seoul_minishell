/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:02:01 by tkong             #+#    #+#             */
/*   Updated: 2023/01/22 01:00:11 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_db *db);

void	subsh(t_db *db)
{
	init(db);
	if (check(db) || token(db) || valid(db))
		error(db);
	execute(db);
}

static void	init(t_db *db)
{
	db->arg_begin = 0;
	db->arg_end = 0;
	untoken(db);
	untool(db);
}
