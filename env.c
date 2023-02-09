/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:52:14 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 03:46:44 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	check_arg(t_a *a);
static void		show_env(t_a *a);
static void		add_env(t_a *a);
static void		make_env(t_a *a, t_i32 i);

void	env(t_a *a)
{
	t_i32	fd[2];

	pipe(fd);
	setself(a, fd);
	a->proc_l += ft_strcpy(a->proc + a->proc_l, "env: ");
	if (a->ac == 1)
		show_env(a);
	else
	{
		if (check_arg(a))
			error(a);
		else
			add_env(a);
	}
	a->proc_l -= ft_strlen("env: ");
	recover(a, fd);
}

static t_i32	check_arg(t_a *a)
{
	t_i32	i;

	i = 0;
	while (++i < a->ac)
	{
		if (!ft_strchr(a->av[i], '='))
		{
			a->errn = ERR_FILEPATH;
			a->erra = a->av[i];
			return (-1);
		}
	}
	return (0);
}

static void	show_env(t_a *a)
{
	t_i32	i;
	t_node	*p;
	t_ev	*cur;

	i = -1;
	p = a->env.hd;
	cur = p->e;
	while (++i < a->env.len)
	{
		write(a->fd[STDOUT__], cur->k, ft_strlen(cur->k));
		if (cur->v)
		{
			write(a->fd[STDOUT__], "=", 1);
			write(a->fd[STDOUT__], cur->v, ft_strlen(cur->v));
		}
		write(a->fd[STDOUT__], "\n", 1);
		p = p->r;
		cur = p->e;
	}
	endout(a, STDOUT__);
}

static void	add_env(t_a *a)
{
	t_i32	i;

	i = 0;
	while (++i < a->ac)
		make_env(a, i);
	show_env(a);
}

static void	make_env(t_a *a, t_i32 i)
{
	t_i8	*key;
	t_i8	*val;
	t_ev	*elem;

	key = getkey__(a->av[i]);
	elem = getelem__(&(a->env), key);
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
		ft_pushb(&(a->env), elem);
	}
}
