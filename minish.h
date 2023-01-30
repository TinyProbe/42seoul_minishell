/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:03:29 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 12:14:17 by tkong            ###   ########.fr       */
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

typedef struct dirent t_dirent;
typedef struct s_tkn
{
	t_i8	*_;
	t_i32	len;
}	t_tkn;
typedef struct s_repl
{
	t_i8	*_;
	t_i32	len;
	t_i32	l;
	t_i32	r;
	t_i32	last;
	t_type	type;
}	t_repl;
typedef struct s_z
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
	t_i32		ab;
	t_i32		ae;
	t_i8		*av[ARG_MAX];
	t_i32		ac;
	t_i8		*ri[REDIR_MAX];
	t_i32		ri_len;
	t_i8		*ro[REDIR_MAX];
	t_i32		ro_len;
	t_conj		conj;
	t_repl		repl[REPL_MAX];
	t_i32		repl_len;
}	t_z;

void	sigtoggle(t_z *z);
void	sigint_rl(t_i32 sig);
void	sigint(t_i32 sig);
void	sigterm(t_i32 sig);
void	sigquit(t_i32 sig);

void	process(t_z *z);
void	parent(t_z *z, t_i32 *fd, pid_t pid);
void	child(t_z *z, t_i32 *fd);

void	redirect(t_z *z);

void	minish(t_z *z);

void	program(t_z *z);
void	subsh(t_z *z);
void	echo(t_z *z);
void	cd(t_z *z);
void	pwd(t_z *z);
void	export__(t_z *z);
void	unset(t_z *z);
void	env(t_z *z);
void	exit__(t_z *z);
void	file_exe(t_z *z);

void	check(t_z *z);
void	bracket(t_z *z, t_i8 *s, t_i32 i);
void	quote(t_z *z);
void	claw(t_z *z);

void	token(t_z *z);
void	untoken(t_z *z);

void	valid(t_z *z);

void	error(t_z *z);

void	execute(t_z *z);

void	subst(t_z *z);
void	repl_env(t_z *z);
void	repl_cmd(t_z *z);
void	apply_repl(t_z *z);
void	repl_wild(t_z *z);
void	join(t_z *z, t_i8 *path, t_bdll *bdll);

void	recwd(t_z *z);
void	output(t_z *z, t_i32 out, t_i32 err);
void	unrepl(t_z *z);
t_i8	*getpath(t_i8 *cwd, t_i8 *arg);
t_i8	*getfile(t_i8 *arg, t_i32 len);
t_bool	isincl(t_i8 *cur, t_i8 *file);
t_i8	**split__(t_i8 *s, t_i8 c);

void	test(t_z *z);

#endif
