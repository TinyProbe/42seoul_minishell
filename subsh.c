/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:02:01 by tkong             #+#    #+#             */
/*   Updated: 2023/01/15 01:40:06 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_db *db);

void	subsh(t_db *db)
{
	init(db);
	if (check(db) || token(db) || exec(db))
		error(db);
}

static void	init(t_db *db)
{
	db->err = 0;
	db->stk_len = 0;
	untoken(db);
}
