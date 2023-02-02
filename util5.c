/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:40:06 by tkong             #+#    #+#             */
/*   Updated: 2023/02/02 17:46:30 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	re_(t_a *a)
{
	t_i32	i;
	t_node	*p;
	t_ev	*cur;

	i = -1;
	p = a->env.hd;
	cur = p->e;
	while (++i < a->env.len && ft_strcmp(cur->k, "_"))
	{
		p = p->r;
		cur = p->e;
	}
	if (i < a->env.len)
	{
		free(cur->v);
		cur->v = ft_strdup(a->av[a->ac - 1]);
	}
}
