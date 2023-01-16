/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:03:29 by tkong             #+#    #+#             */
/*   Updated: 2023/01/17 04:13:58 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include "ft/ft.h"
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CMD_MAX	10000
# define STK_MAX	10000
# define TKN_MAX	10000
# define PROC_MAX	10000
# define CWD_MAX	10000
# define TOT_MAX	100000
# define BUF_MAX	10000
# define ELEM_MAX	10000
# define PROMPT		"minish> "

typedef enum e_sigstat
{
	SIGSTAT_WAITCMD = 1,
	SIGSTAT_PROCCMD,
}	t_sigstat;
typedef enum e_errno
{
	ERRNO_FORMAT = 1,
	ERRNO_RESTRICT,
	ERRNO_LONGCMD,
	ERRNO_LONGCWD,
	ERRNO_UNKNOWN,
	ERRNO_MAX,
}	t_errno;

typedef struct s_elem
{
	t_i32	begin;
	t_i32	end;
	t_i32	fd;
}	t_elem;
typedef struct s_db
{
	t_i32		lv;
	t_sigstat	sigstat;
	const t_i8	*errmsg[ERRNO_MAX];
	t_errno		errno;
	t_i8		cmd[CMD_MAX];
	t_i32		len;
	t_i8		stk[STK_MAX];
	t_i32		stk_len;
	t_i8		*tkn[TKN_MAX];
	t_i32		tkn_len;
	t_i8		proc[PROC_MAX];
	t_i32		proc_len;
	t_i8		cwd[CWD_MAX];
	t_i32		cwd_len;
	t_i8		tot[TOT_MAX];
	t_i32		tot_len;
	t_i8		buf[BUF_MAX];
	t_i32		buf_len;
	t_elem		elem[ELEM_MAX];
	t_i32		elem_len;
	t_i32		io;
	t_i32		ie;
	t_i32		o;
	t_i32		e;
	t_i32		rtn;
}	t_db;

void	sigtoggle(t_db *db);
void	sigint_rl(t_i32 sig);
void	sigint(t_i32 sig);
void	sigterm(t_i32 sig);
void	sigquit(t_i32 sig);

void	process(t_db *db, void (*ftr)(t_db *));

void	minish(t_db *db);
void	subsh(t_db *db);

t_i32	check(t_db *db);
void	bracket(t_db *db, t_i32 i);
void	quote(t_db *db);
void	claw(t_db *db);

t_i32	token(t_db *db);
void	untoken(t_db *db);

t_i32	exec(t_db *db);

void	error(t_db *db);

void	recwd(t_db *db);
// void	pipelink(int *fd, int dir);

#endif
