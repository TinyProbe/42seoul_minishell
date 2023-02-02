/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:28:13 by tkong             #+#    #+#             */
/*   Updated: 2023/02/02 17:53:13 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	addln(t_a *a, t_i32 i, t_i32 j)
{
	ft_memcpy(a->lln + a->lln_l, a->buf + j, i - j);
	a->lln_l += (i - j);
}

void	lastln(t_a *a)
{
	t_i32	i;
	t_i32	j;

	i = a->lln_l;
	j = 0;
	while (i--)
		if (a->lln[i] == '\n')
			break ;
	while (++i < a->lln_l)
		a->lln[j++] = a->lln[i];
	a->lln[j] = '\0';
	a->lln_l = j;
}

t_i8	*getkey__(const t_i8 *s)
{
	t_i32	i;

	i = -1;
	while (s[++i] && s[i] != '=')
		;
	return (ft_strndup(s, i));
}

t_i8	*getval__(const t_i8 *s)
{
	t_i32	i;

	--s;
	while (*++s && *s != '=')
		;
	if (*s == '\0')
		return (NULL);
	++s;
	i = -1;
	while (s[++i])
		;
	return (ft_strndup(s, i));
}

t_i8	*getenv__(t_a *a, const t_i8 *s)
{
	t_i32	i;
	t_node	*p;
	t_i32	len;
	t_ev	*cur;

	i = -1;
	p = a->exp.hd;
	len = a->exp.len;
	if (!ft_strcmp(s, "_"))
	{
		p = a->env.hd;
		len = a->env.len;
	}
	cur = p->e;
	while (++i < len && ft_strcmp(cur->k, s))
	{
		p = p->r;
		cur = p->e;
	}
	if (i == len)
		return (NULL);
	return (cur->v);
}
