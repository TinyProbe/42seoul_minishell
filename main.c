/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:00:54 by tkong             #+#    #+#             */
/*   Updated: 2023/01/15 17:08:21 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	init(t_db *db);
static void		seterr(t_db *db);

t_i32	main(void)
{
	t_db	db;

	if (init(&db))
		error(&db);
	minish(&db);
	exit(0);
}

static t_i32	init(t_db *db)
{
	db->sigstat = SIGSTAT_PROCCMD;
	sigtoggle(db);
	seterr(db);
	db->err = 0;
	db->len = 0;
	db->tkn_len = 0;
	db->proc_len = ft_strcpy(db->proc, "minish");
	if (recwd(db))
		return (-1);
	return (0);
}

static void seterr(t_db *db)
{
	db->errmsg[ERRNO_FORMAT] = "Exec format error.";
	db->errmsg[ERRNO_RESTRICT] = "Restricted function.";
	db->errmsg[ERRNO_LONGCMD] = "Command too long.";
	db->errmsg[ERRNO_LONGCWD] = "Current work directory too long.";
	db->errmsg[ERRNO_UNKNOWN] = "Unknown error.";
}
