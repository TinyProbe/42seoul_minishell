/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:00:54 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 13:49:38 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_a *a);
static void	seterr(t_a *a);

t_i32	main(void)
{
	t_a	a;

	init(&a);
	minish(&a);
	exit(0);
}

static void	init(t_a *a)
{
	a->sigstat = SIGS_PROCCMD;
	sigtoggle(a);
	seterr(a);
	a->errarg = NULL;
	a->errno = ERRNO_NONE;
	a->cmd_l = 0;
	a->stk_l = 0;
	a->tkn_l = 0;
	a->proc_l = ft_strcpy(a->proc, "minish: ");
	recwd(a);
	a->buf_l = 0;
	a->fd[STDIN__] = STDIN__;
	a->fd[STDOUT__] = STDOUT__;
	a->fd[STDERR__] = STDERR__;
	a->rtn = 0;
	a->ac = 0;
	a->ri_l = 0;
	a->ro_l = 0;
	a->conj = CONJ_NONE;
	a->rp_l = 0;
}

static void	seterr(t_a *a)
{
	a->errmsg[ERRNO_FORMAT] = "syntax error near unexpected token.";
	a->errmsg[ERRNO_RESTRICT] = "Restricted function.";
	a->errmsg[ERRNO_LONGCMD] = "Command too long.";
	a->errmsg[ERRNO_LONGCWD] = "Current work directory too long.";
	a->errmsg[ERRNO_FILEPATH] = "No such file or directory.";
	a->errmsg[ERRNO_FILEFAIL] = "File open failed.";
	a->errmsg[ERRNO_NOCMD] = "command not found.";
	a->errmsg[ERRNO_UNKNOWN] = "Unknown error.";
}
