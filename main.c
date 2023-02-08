/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:00:54 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 22:04:31 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_a *a);
static void	initenv(t_a *a);
static void	initexp(t_a *a);
static void	seterr(t_a *a);

t_a	*g_a;

t_i32	main(void)
{
	t_a	a;

	g_a = &a;
	a.sigstat = SIGS_PROCCMD;
	sigtoggle(&a);
	seterr(&a);
	a.erra = NULL;
	a.errn = ERR_NONE;
	a.lln_l = 0;
	a.cmd_l = 0;
	a.stk_l = 0;
	a.tkn_l = 0;
	a.proc_l = ft_strcpy(a.proc, "minish: ");
	recwd(&a);
	a.buf_l = 0;
	a.fd[STDIN__] = STDIN__;
	a.fd[STDOUT__] = STDOUT__;
	a.fd[STDERR__] = STDERR__;
	init(&a);
	minish(&a);
	exit(0);
}

static void	init(t_a *a)
{
	a->rtn = 0;
	a->sigrtn = 0;
	a->ac = 0;
	a->ext_l = 0;
	a->ri_l = 0;
	a->ro_l = 0;
	a->conj = CONJ_NONE;
	a->rp_l = 0;
	a->dup2_cnt = 0;
	a->dup2_cnt_old = 0;
	initenv(a);
	initexp(a);
}

static void	initenv(t_a *a)
{
	t_i32	i;
	t_ev	*tmp;

	a->env.hd = NULL;
	a->env.len = 0;
	i = -1;
	while (environ[++i])
	{
		tmp = (t_ev *) malloc(sizeof(t_ev));
		tmp->k = getkey__(environ[i]);
		if (!ft_strcmp(tmp->k, "OLDPWD"))
		{
			free(tmp->k);
			free(tmp);
			continue ;
		}
		tmp->v = getval__(environ[i]);
		ft_pushb(&(a->env), tmp);
	}
}

static void	initexp(t_a *a)
{
	t_i32	i;
	t_ev	*tmp;

	a->exp.hd = NULL;
	a->exp.len = 0;
	i = -1;
	while (environ[++i])
	{
		tmp = (t_ev *) malloc(sizeof(t_ev));
		tmp->k = getkey__(environ[i]);
		if (ft_strcmp(tmp->k, "OLDPWD"))
			tmp->v = getval__(environ[i]);
		else
			tmp->v = NULL;
		if (ft_strcmp(tmp->k, "_"))
			ft_pushb(&(a->exp), tmp);
		else
		{
			free(tmp->k);
			if (tmp->v)
				free(tmp->v);
			free(tmp);
		}
	}
}

static void	seterr(t_a *a)
{
	a->errm[ERR_FORMAT] = "Syntax error near unexpected token.";
	a->errm[ERR_RESTRICT] = "Restricted function.";
	a->errm[ERR_LONGCMD] = "Command too long.";
	a->errm[ERR_LONGCWD] = "Current work directory too long.";
	a->errm[ERR_FILEPATH] = "No such file or directory.";
	a->errm[ERR_FILEFAIL] = "File open failed.";
	a->errm[ERR_NOCMD] = "Command not found.";
	a->errm[ERR_IDENTI] = "Not a valid identifier.";
	a->errm[ERR_NUMERIC] = "Numeric argument required.";
	a->errm[ERR_TOOMANY] = "Too many arguments.";
	a->errm[ERR_UNKNOWN] = "Unknown error.";
}
