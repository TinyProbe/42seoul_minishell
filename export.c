/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:52:14 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 03:46:44 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	show_exp(t_a *a);
static void	add_exp(t_a *a);
static void	make_exp(t_a *a, t_i32 i);

void	export__(t_a *a)
{
	t_i32	fd[2];

	pipe(fd);
	setself(a, fd);
	a->proc_l += ft_strcpy(a->proc + a->proc_l, "export: ");
	if (a->ac == 1)
		show_exp(a);
	else
	{
		if (check_env(a, 0, 0, NULL))
			error(a);
		else
			add_exp(a);
	}
	sync_env(a);
	a->proc_l -= ft_strlen("export: ");
	recover(a, fd);
}

static void	show_exp(t_a *a)
{
	t_i32	i;
	t_node	*p;
	t_ev	*cur;

	i = -1;
	p = a->exp.hd;
	cur = p->e;
	while (++i < a->exp.len)
	{
		write(a->fd[STDOUT__], DECLARE, ft_strlen(DECLARE));
		write(a->fd[STDOUT__], cur->k, ft_strlen(cur->k));
		if (cur->v)
		{
			write(a->fd[STDOUT__], "=\"", 2);
			write(a->fd[STDOUT__], cur->v, ft_strlen(cur->v));
			write(a->fd[STDOUT__], "\"", 1);
		}
		write(a->fd[STDOUT__], "\n", 1);
		p = p->r;
		cur = p->e;
	}
	endout(a, STDOUT__);
}

static void	add_exp(t_a *a)
{
	t_i32	i;
	t_i8	*k;

	i = 0;
	while (++i < a->ac)
	{
		k = getkey__(a->av[i]);
		if (ft_strcmp(k, "_"))
			make_exp(a, i);
		free(k);
	}
}

static void	make_exp(t_a *a, t_i32 i)
{
	t_i8	*key;
	t_i8	*val;
	t_ev	*elem;

	key = getkey__(a->av[i]);
	elem = getelem__(&(a->exp), key);
	if (elem)
	{
		free(key);
		val = getval__(a->av[i]);
		if (!val)
			return ;
		if (elem->v)
			free(elem->v);
		elem->v = val;
	}
	else
	{
		elem = (t_ev *) malloc(sizeof(t_ev));
		elem->k = key;
		elem->v = getval__(a->av[i]);
		ft_pushb(&(a->exp), elem);
	}
}
