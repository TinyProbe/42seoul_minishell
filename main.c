/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:00:54 by tkong             #+#    #+#             */
/*   Updated: 2023/01/31 15:51:29 by tkong            ###   ########.fr       */
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
	a->erra = NULL;
	a->errn = ERR_NONE;
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
	a->errm[ERR_FORMAT] = "syntax error near unexpected token.";
	a->errm[ERR_RESTRICT] = "Restricted function.";
	a->errm[ERR_LONGCMD] = "Command too long.";
	a->errm[ERR_LONGCWD] = "Current work directory too long.";
	a->errm[ERR_FILEPATH] = "No such file or directory.";
	a->errm[ERR_FILEFAIL] = "File open failed.";
	a->errm[ERR_NOCMD] = "command not found.";
	a->errm[ERR_UNKNOWN] = "Unknown error.";
}
