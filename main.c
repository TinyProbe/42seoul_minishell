/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:00:54 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 11:06:39 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_z *z);
static void	seterr(t_z *z);

t_i32	main(void)
{
	t_z	z;

	init(&z);
	minish(&z);
	exit(0);
}

static void	init(t_z *z)
{
	z->sigstat = SIGS_PROCCMD;
	sigtoggle(z);
	seterr(z);
	z->errarg = NULL;
	z->errno = ERRNO_NONE;
	z->len = 0;
	z->stk_len = 0;
	z->tkn_len = 0;
	z->proc_len = ft_strcpy(z->proc, "minish: ");
	recwd(z);
	z->buf_len = 0;
	z->fd[STDIN__] = STDIN__;
	z->fd[STDOUT__] = STDOUT__;
	z->fd[STDERR__] = STDERR__;
	z->rtn = 0;
	z->ac = 0;
	z->ri_len = 0;
	z->ro_len = 0;
	z->conj = CONJ_NONE;
	z->repl_len = 0;
}

static void	seterr(t_z *z)
{
	z->errmsg[ERRNO_FORMAT] = "syntax error near unexpected token.";
	z->errmsg[ERRNO_RESTRICT] = "Restricted function.";
	z->errmsg[ERRNO_LONGCMD] = "Command too long.";
	z->errmsg[ERRNO_LONGCWD] = "Current work directory too long.";
	z->errmsg[ERRNO_FILEPATH] = "No such file or directory.";
	z->errmsg[ERRNO_FILEFAIL] = "File open failed.";
	z->errmsg[ERRNO_NOCMD] = "command not found.";
	z->errmsg[ERRNO_UNKNOWN] = "Unknown error.";
}
