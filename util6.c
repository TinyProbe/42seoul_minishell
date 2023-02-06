/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:03:19 by tkong             #+#    #+#             */
/*   Updated: 2023/02/06 18:05:26 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	no_del(t_a *a, t_node *p, t_ev *cur, t_ev *cur2);
static void	no_add(t_a *a, t_node *p, t_ev *cur, t_ev *cur2);

void	sync_env(t_a *a)
{
	no_del(a, a->env.hd, NULL, NULL);
	no_add(a, a->exp.hd, NULL, NULL);
}

static void	no_del(t_a *a, t_node *p, t_ev *cur, t_ev *cur2)
{
	t_i32	i;

	i = -1;
	cur = p->e;
	while (++i < a->env.len)
	{
		if (ft_strcmp(cur->k, "_"))
		{
			cur2 = getelem__(&(a->exp), cur->k);
			if (cur2 && cur2->v)
			{
				free(cur->v);
				cur->v = ft_strdup(cur2->v);
			}
			else
			{
				del_env(&(a->env), cur->k);
				--i;
			}
		}
		p = p->r;
		cur = p->e;
	}
}

static void	no_add(t_a *a, t_node *p, t_ev *cur, t_ev *cur2)
{
	t_i32	i;

	i = -1;
	cur = p->e;
	while (++i < a->exp.len)
	{
		if (ft_strcmp(cur->k, "OLDPWD") && cur->v)
		{
			cur2 = getelem__(&(a->env), cur->k);
			if (cur2)
			{
				free(cur2->v);
				cur2->v = ft_strdup(cur->v);
			}
			else
			{
				cur2 = (t_ev *) malloc(sizeof(t_ev));
				cur2->k = ft_strdup(cur->k);
				cur2->v = ft_strdup(cur->v);
				ft_pushb(&(a->env), cur2);
			}
		}
		p = p->r;
		cur = p->e;
	}
}

t_i32	check_env(t_a *a, t_i32 i, t_i32 j, t_i8 *k)
{
	while (++i < a->ac)
	{
		k = getkey__(a->av[i]);
		if (!ft_isalpha(k[0]) && k[0] != '_')
		{
			free(k);
			a->errn = ERR_IDENTI;
			a->erra = a->av[i];
			return (-1);
		}
		j = -1;
		while (k[++j])
		{
			if (!ft_isalnum(k[j]) && k[j] != '_')
			{
				free(k);
				a->errn = ERR_IDENTI;
				a->erra = a->av[i];
				return (-1);
			}
		}
		free(k);
	}
	return (0);
}

t_i32	check_env2(t_a *a, t_i32 i, t_i32 j)
{
	while (++i < a->ac)
	{
		if (!ft_isalpha(a->av[i][0]) && a->av[i][0] != '_')
		{
			a->errn = ERR_IDENTI;
			a->erra = a->av[i];
			return (-1);
		}
		j = -1;
		while (a->av[i][++j])
		{
			if (!ft_isalnum(a->av[i][j]) && a->av[i][j] != '_')
			{
				a->errn = ERR_IDENTI;
				a->erra = a->av[i];
				return (-1);
			}
		}
	}
	return (0);
}
