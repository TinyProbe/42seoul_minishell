/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bdll2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 01:15:02 by tkong             #+#    #+#             */
/*   Updated: 2023/02/02 16:32:28 by tkong            ###   ########.fr       */
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
	if (idx <= bdll->len / 2)
		while (idx--)
			p = p->r;
	else
		while (idx++ < bdll->len)
			p = p->l;
	return (p);
}

void	*ft_at(t_bdll *bdll, t_i32 idx)
{
	return (ft_search(bdll, idx)->e);
}

void	*ft_setat(t_bdll *bdll, t_i32 idx, void *e)
{
	t_node	*p;
	void	*tmp;

	p = ft_search(bdll, idx);
	tmp = p->e;
	p->e = e;
	return (tmp);
}
