/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:03:29 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 09:58:48 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include "ft/ft.h"
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CMD_MAX	100000
# define STK_MAX	10000
# define TKN_MAX	10000
# define PROC_MAX	10000
# define CWD_MAX	10000
# define BUF_MAX	100000
# define ARG_MAX	10000
# define REDIR_MAX	10000
# define REPL_MAX	10000
# define PROMPT		"minish> "

typedef enum e_sigstat
{
	SIGS_WAITCMD,
	SIGS_PROCCMD,
}	t_sigstat;
typedef enum e_errno
{
	ERRNO_NONE,
	ERRNO_FORMAT,
	ERRNO_RESTRICT,
	ERRNO_LONGCMD,
	ERRNO_LONGCWD,
	ERRNO_FILEPATH,
	ERRNO_FILEFAIL,
	ERRNO_NOCMD,
	ERRNO_UNKNOWN,
	ERRNO_MAX,
	EXIT,
}	t_errno;
typedef enum e_conj
{
	CONJ_NONE,
	CONJ_AND,
	CONJ_ANDAND,
	CONJ_OR,
	CONJ_OROR,
}	t_conj;
typedef enum e_prog
{
	PROG_NONE,
	PROG_SUBSH,
	PROG_ECHO,
	PROG_CD,
	PROG_PWD,
	PROG_EXPORT,
	PROG_UNSET,
	PROG_ENV,
	PROG_EXIT,
}	t_prog;
typedef enum e_type
{
	TYPE_NONE,
	TYPE_ENV,
	TYPE_ENV_RTN,
	TYPE_CMD,
}	t_type;

typedef struct s_tkn
{
	t_i8	*_;
	t_i32	len;
}	t_tkn;
typedef struct s_repl
{
	t_i32	l;
	t_i32	r;
	t_i32	last;
	t_type	type;
	t_i8	*_;
	t_i32	len;
}	t_repl;
typedef struct s_db
{
	t_sigstat	sigstat;
	const t_i8	*errmsg[ERRNO_MAX];
	t_i8		*errarg;
	t_errno		errno;
	t_i8		cmd[CMD_MAX];
	t_i32		len;
	t_i8		stk[STK_MAX];
	t_i32		stk_len;
	t_tkn		tkn[TKN_MAX];
	t_i32		tkn_len;
	t_i8		proc[PROC_MAX];
	t_i32		proc_len;
	t_i8		cwd[CWD_MAX];
	t_i32		cwd_len;
	t_i8		buf[BUF_MAX];
	t_i32		buf_len;
	t_i32		fd[3];
	t_i32		rtn;
	t_i32		arg_b;
	t_i32		arg_e;
	t_i8		*av[ARG_MAX];
	t_i32		ac;
	t_i8		*ri[REDIR_MAX];
	t_i32		ri_len;
	t_i8		*ro[REDIR_MAX];
	t_i32		ro_len;
	t_conj		conj;
	t_repl		repl[REPL_MAX];
	t_i32		repl_len;
}	t_db;

void	sigtoggle(t_db *db);
void	sigint_rl(t_i32 sig);
void	sigint(t_i32 sig);
void	sigterm(t_i32 sig);
void	sigquit(t_i32 sig);

void	process(t_db *db);
void	parent(t_db *db, t_i32 *fd, pid_t pid);
void	child(t_db *db, t_i32 *fd);

void	redirect(t_db *db);

void	minish(t_db *db);

void	program(t_db *db);
void	subsh(t_db *db);
void	echo(t_db *db);
void	cd(t_db *db);
void	pwd(t_db *db);
void	export__(t_db *db);
void	unset(t_db *db);
void	env(t_db *db);
void	exit__(t_db *db);
void	file_exe(t_db *db);

void	check(t_db *db);
void	bracket(t_db *db, t_i8 *s, t_i32 i);
void	quote(t_db *db);
void	claw(t_db *db);

void	token(t_db *db);
void	untoken(t_db *db);

void	valid(t_db *db);

void	error(t_db *db);

void	execute(t_db *db);

void	subst(t_db *db);
void	repl_env(t_db *db);
void	repl_cmd(t_db *db);
void	apply_repl(t_db *db);
void	repl_wild(t_db *db);

void	recwd(t_db *db);
void	output(t_db *db, t_i32 out, t_i32 err);
void	unrepl(t_db *db);

#endif
