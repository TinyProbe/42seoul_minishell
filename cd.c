/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:52:14 by tkong             #+#    #+#             */
/*   Updated: 2023/02/02 17:09:34 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	repwd(t_a *a);
static void	repwd_env(t_a *a);
static void	repwd_exp(t_a *a);

void	cd(t_a *a)
{
	a->proc_l += ft_strcpy(a->proc + a->proc_l, "cd: ");
	if (chdir(a->av[1]))
	{
		a->errn = ERR_FILEPATH;
		a->erra = a->av[1];
		error(a);
	}
	recwd(a);
	repwd(a);
	a->proc_l -= ft_strlen("cd: ");
}

static void	repwd(t_a *a)
{
	repwd_env(a);
	repwd_exp(a);
}

static void	repwd_env(t_a *a)
{
	t_node	*p;
	t_ev	*cur;

	p = a->env.hd;
	while (TRUE)
	{
		cur = p->e;
		if (!ft_strcmp(cur->k, "PWD"))
			break ;
		p = p->r;
	}
	cur->v = ft_strndup(a->cwd, a->cwd_l);
}

static void	repwd_exp(t_a *a)
{
	t_node	*p;
	t_ev	*cur;
	t_ev	*old;

	p = a->exp.hd;
	while (TRUE)
	{
		cur = p->e;
		if (!ft_strcmp(cur->k, "PWD"))
			break ;
		p = p->r;
	}
	p = a->exp.hd;
	while (TRUE)
	{
		old = p->e;
		if (!ft_strcmp(old->k, "OLDPWD"))
			break ;
		p = p->r;
	}
	free(old->v);
	old->v = cur->v;
	cur->v = ft_strndup(a->cwd, a->cwd_l);
}
