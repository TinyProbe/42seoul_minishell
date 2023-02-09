/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:52:14 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 03:46:44 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	repwd_env(t_a *a);
static void	repwd_exp(t_a *a);

void	cd(t_a *a)
{
	t_i8	*path;
	t_i32	fd[2];

	pipe(fd);
	setself(a, fd);
	a->proc_l += ft_strcpy(a->proc + a->proc_l, "cd: ");
	if (a->ac == 1)
		path = getenv__(a, "HOME");
	else
		path = a->av[1];
	if (chdir(path))
	{
		a->errn = ERR_FILEPATH;
		a->erra = path;
		error(a);
	}
	recwd(a);
	repwd_env(a);
	repwd_exp(a);
	sync_env(a);
	a->proc_l -= ft_strlen("cd: ");
	recover(a, fd);
}

static void	repwd_env(t_a *a)
{
	t_ev	*elem;

	elem = getelem__(&(a->env), "PWD");
	if (elem)
	{
		if (elem->v)
			free(elem->v);
	}
	else
	{
		elem = (t_ev *) malloc(sizeof(t_ev));
		elem->k = ft_strdup("PWD");
		ft_pushb(&(a->env), elem);
	}
	elem->v = ft_strndup(a->cwd, a->cwd_l);
}

static void	repwd_exp(t_a *a)
{
	t_ev	*cur;
	t_ev	*old;

	cur = getelem__(&(a->exp), "PWD");
	old = getelem__(&(a->exp), "OLDPWD");
	if (!cur)
	{
		cur = (t_ev *) malloc(sizeof(t_ev));
		cur->k = ft_strdup("PWD");
		cur->v = NULL;
		ft_pushb(&(a->exp), cur);
	}
	if (!old)
	{
		old = (t_ev *) malloc(sizeof(t_ev));
		old->k = ft_strdup("OLDPWD");
		old->v = NULL;
		ft_pushb(&(a->exp), old);
	}
	if (old->v)
		free(old->v);
	old->v = cur->v;
	cur->v = ft_strndup(a->cwd, a->cwd_l);
}
