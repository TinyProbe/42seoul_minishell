/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:00:54 by tkong             #+#    #+#             */
/*   Updated: 2023/01/17 04:13:58 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_db *db);
static void	seterr(t_db *db);

t_i32	main(void)
{
	t_db	db;

	init(&db);
	minish(&db);
	exit(0);
}

static void	init(t_db *db)
{
	db->lv = 0;
	db->sigstat = SIGSTAT_PROCCMD;
	sigtoggle(db);
	seterr(db);
	db->errno = 0;
	db->len = 0;
	db->stk_len = 0;
	db->tkn_len = 0;
	db->proc_len = ft_strcpy(db->proc, "minish");
	db->tot_len = 0;
	db->buf_len = 0;
	db->elem_len = 0;
	db->io = STDIN__;
	db->ie = STDIN__;
	db->o = STDOUT__;
	db->e = STDERR__;
	db->rtn = 0;
}

static void	seterr(t_db *db)
{
	db->errmsg[ERRNO_FORMAT] = "Exec format error.";
	db->errmsg[ERRNO_RESTRICT] = "Restricted function.";
	db->errmsg[ERRNO_LONGCMD] = "Command too long.";
	db->errmsg[ERRNO_LONGCWD] = "Current work directory too long.";
	db->errmsg[ERRNO_UNKNOWN] = "Unknown error.";
}
