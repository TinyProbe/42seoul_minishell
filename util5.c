/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:40:06 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 04:35:44 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	re_(t_a *a)
{
	t_ev	*elem;

	elem = getelem__(&(a->env), "_");
	if (elem)
	{
		if (elem->v)
			free(elem->v);
	}
	else
	{
		elem = (t_ev *) malloc(sizeof(t_ev));
		elem->k = ft_strdup("_");
		ft_pushb(&(a->env), elem);
	}
	if (!ft_strcmp(a->av[0], "env"))
		elem->v = ft_strdup("env");
	else
		elem->v = ft_strdup(a->av[a->ac - 1]);
}

t_node	*getnode__(t_bdll *map, const t_i8 *k)
{
	t_node	*p;

	p = map->hd;
	while (TRUE)
	{
		if (!ft_strcmp(((t_ev *)(p->e))->k, k))
			return (p);
		p = p->r;
		if (p == map->hd)
			break ;
	}
	return (NULL);
}

t_ev	*getelem__(t_bdll *map, const t_i8 *k)
{
	t_node	*p;

	p = getnode__(map, k);
	if (p)
		return (p->e);
	return (NULL);
}

void	del_env(t_bdll *map, const t_i8 *k)
{
	t_i32	i;
	t_node	*p;
	t_ev	*e;

	i = -1;
	p = map->hd;
	e = p->e;
	while (++i < map->len)
	{
		if (!ft_strcmp(e->k, k))
		{
			e = ft_popat(map, i);
			free(e->k);
			free(e->v);
			free(e);
			break ;
		}
		p = p->r;
		e = p->e;
	}
}

t_i32	cmdtype(t_a *a)
{
	if (a->dup2_cnt)
		return (0);
	if (a->cmd_l || (a->ac && (!ft_strcmp(a->av[0], "cd")
				|| !ft_strcmp(a->av[0], "env")
				|| !ft_strcmp(a->av[0], "export")
				|| !ft_strcmp(a->av[0], "unset")
				|| !ft_strcmp(a->av[0], "exit")
				|| !ft_strcmp(a->av[0], "echo")
				|| !ft_strcmp(a->av[0], "pwd")
				|| a->av[0][0] == '(')))
		return (1);
	return (0);
}
