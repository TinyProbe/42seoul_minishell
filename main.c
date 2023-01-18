/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:00:54 by tkong             #+#    #+#             */
/*   Updated: 2023/01/19 04:35:22 by tkong            ###   ########.fr       */
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
	db->sigstat = SIGSTAT_PROCCMD;
	sigtoggle(db);
	seterr(db);
	db->errno = 0;
	db->len = 0;
	db->stk_len = 0;
	db->tkn_len = 0;
	db->proc_len = ft_strcpy(db->proc, "minish: ");
	db->buf_len = 0;
	db->fd[STDIN__] = STDIN__;
	db->fd[STDOUT__] = STDOUT__;
	db->fd[STDERR__] = STDERR__;
	db->rtn = 0;
	db->ftr = subsh;
	db->ac = 0;
	db->opt = NULL;
	db->rein_len = 0;
	db->reout_len = 0;
	db->pipe = FALSE;
}

static void	seterr(t_db *db)
{
	db->errmsg[ERRNO_FORMAT] = "syntax error near unexpected token.";
	db->errmsg[ERRNO_RESTRICT] = "Restricted function.";
	db->errmsg[ERRNO_LONGCMD] = "Command too long.";
	db->errmsg[ERRNO_LONGCWD] = "Current work directory too long.";
	db->errmsg[ERRNO_FILEPATH] = "No such file or directory.";
	db->errmsg[ERRNO_FILEFAIL] = "File open failed.";
	db->errmsg[ERRNO_UNKNOWN] = "Unknown error.";
}
