/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bdll.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 01:15:01 by tkong             #+#    #+#             */
/*   Updated: 2023/02/05 16:23:56 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	ft_pushf(t_bdll *bdll, void *e)
{
	ft_pushb(bdll, e);
	bdll->hd = bdll->hd->l;
}

void	ft_pushb(t_bdll *bdll, void *e)
{
	t_node	*tmp;

	if (bdll->hd)
	{
		tmp = bdll->hd->l;
		bdll->hd->l = (t_node *) malloc(sizeof(t_node));
		bdll->hd->l->e = e;
		bdll->hd->l->l = tmp;
		bdll->hd->l->r = bdll->hd;
		tmp->r = bdll->hd->l;
	}
	else
	{
		bdll->hd = (t_node *) malloc(sizeof(t_node));
		bdll->hd->e = e;
		bdll->hd->l = bdll->hd;
		bdll->hd->r = bdll->hd;
	}
	bdll->len++;
}

void	*ft_popf(t_bdll *bdll)
{
	void	*rtn;
	t_node	*tmp;

	rtn = bdll->hd->e;
	if (bdll->hd == bdll->hd->r)
	{
		free(bdll->hd);
		bdll->hd = NULL;
	}
	else
	{
		bdll->hd->l->r = bdll->hd->r;
		bdll->hd->r->l = bdll->hd->l;
		tmp = bdll->hd->r;
		free(bdll->hd);
		bdll->hd = tmp;
	}
	bdll->len--;
	return (rtn);
}

void	*ft_popb(t_bdll *bdll)
{
	bdll->hd = bdll->hd->l;
	return (ft_popf(bdll));
}

void	*ft_popat(t_bdll *bdll, t_i32 idx)
{
	t_node	*dst;
	void	*rtn;

	dst = ft_search(bdll, idx);
	rtn = dst->e;
	if (bdll->hd == dst)
		bdll->hd = dst->r;
	dst->l->r = dst->r;
	dst->r->l = dst->l;
	free(dst);
	if (!--(bdll->len))
		bdll->hd = NULL;
	return (rtn);
}
