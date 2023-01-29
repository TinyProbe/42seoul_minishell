/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bdll2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 01:15:02 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 06:55:04 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	*ft_front(t_bdll *bdll)
{
	return (bdll->hd->e);
}

void	*ft_back(t_bdll *bdll)
{
	return (bdll->hd->l->e);
}

t_node	*ft_search(t_bdll *bdll, t_i32 idx)
{
	t_node	*p;

	p = bdll->hd;
	if (bdll->len / 2 >= idx)
		while (idx--)
			p = p->r;
	else
		while (bdll->len - idx--)
			p = p->l;
	return (p);
}

void	*ft_at(t_bdll *bdll, t_i32 idx)
{
	return (ft_search(bdll, idx)->e);
}

void	ft_setat(t_bdll *bdll, t_i32 idx, void *e)
{
	ft_search(bdll, idx)->e = e;
}
