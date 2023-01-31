/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:03:29 by tkong             #+#    #+#             */
/*   Updated: 2023/01/31 15:57:53 by tkong            ###   ########.fr       */
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
typedef enum e_err
{
	ERR_NONE,
	ERR_FORMAT,
	ERR_RESTRICT,
	ERR_LONGCMD,
	ERR_LONGCWD,
	ERR_FILEPATH,
	ERR_FILEFAIL,
	ERR_NOCMD,
	ERR_UNKNOWN,
	ERR_MAX,
}	t_err;
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

typedef struct dirent t_dirent;
typedef struct s_tkn
{
	t_i8	*_;
	t_i32	len;
}	t_tkn;
typedef struct s_rp
{
	t_i8	*_;
	t_i32	len;
	t_i32	l;
	t_i32	r;
	t_i32	last;
	t_type	type;
}	t_rp;
typedef struct s_a
{
	t_sigstat	sigstat;
	const t_i8	*errm[ERR_MAX];
	t_i8		*erra;
	t_err		errn;
	t_i8		cmd[CMD_MAX];
	t_i32		cmd_l;
	t_i8		stk[STK_MAX];
	t_i32		stk_l;
	t_tkn		tkn[TKN_MAX];
	t_i32		tkn_l;
	t_i8		proc[PROC_MAX];
	t_i32		proc_l;
	t_i8		cwd[CWD_MAX];
	t_i32		cwd_l;
	t_i8		buf[BUF_MAX];
	t_i32		buf_l;
	t_i32		fd[3];
	t_i32		rtn;
	t_i32		ab;
	t_i32		ae;
	t_i8		*av[ARG_MAX];
	t_i32		ac;
	t_i8		*ri[REDIR_MAX];
	t_i32		ri_l;
	t_i8		*ro[REDIR_MAX];
	t_i32		ro_l;
	t_conj		conj;
	t_rp		rp[REPL_MAX];
	t_i32		rp_l;
}	t_a;

extern char **environ;

void	sigtoggle(t_a *a);
void	sigint_rl(t_i32 sig);
void	sigint(t_i32 sig);
void	sigterm(t_i32 sig);
void	sigquit(t_i32 sig);

t_i32	self(t_a *a);
t_i32	process(t_a *a);
void	parent(t_a *a, t_i32 *fd, pid_t pid);
void	child(t_a *a, t_i32 *fd);

void	redirect(t_a *a);

void	minish(t_a *a);

void	program(t_a *a);
void	subsh(t_a *a);
void	echo(t_a *a);
void	cd(t_a *a);
void	pwd(t_a *a);
void	export__(t_a *a);
void	unset(t_a *a);
void	env(t_a *a);
void	exit__(t_a *a);
void	file_exe(t_a *a);

t_i32	check(t_a *a);
void	bracket(t_a *a, t_i8 *s, t_i32 i);
void	quote(t_a *a);
void	claw(t_a *a);

t_i32	token(t_a *a);

t_i32	valid(t_a *a);

t_i32	exec(t_a *a);
t_i32	subst(t_a *a);
void	rp_env(t_a *a);
void	rp_cmd(t_a *a);
void	apply_rp(t_a *a);
t_i32	rp_wild(t_a *a);
void	join(t_a *a, t_i8 *path, t_bdll *bdll);

void	error(t_a *a);

void	recwd(t_a *a);
void	output(t_a *a, t_i32 out, t_i32 err);
void	endout(t_a *a, t_i8 fd);
void	untoken(t_a *a);
void	unrepl(t_a *a);
t_i8	*getpath(t_i8 *cwd, t_i8 *arg);
t_i8	*getfile(t_i8 *arg, t_i32 len);
t_bool	isincl(t_i8 *cur, t_i8 *file);

void	test(t_a *a);

#endif
