/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 08:04:16 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 13:40:29 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	calclen(t_a *a, t_i8 *path, t_bdll *bdll);
static void		cpy(t_a *a, t_i8 *path, t_bdll *bdll);

void	join(t_a *a, t_i8 *path, t_bdll *bdll)
{
	calclen(a, path, bdll);
	cpy(a, path, bdll);
}

static t_i32 calclen(t_a *a, t_i8 *path, t_bdll *bdll)
{
	t_node	*p;
	t_i32	len;
	t_i32	i;

	p = bdll->hd;
	len = bdll->len;
	len += ft_strlen(path) * bdll->len;
	i = -1;
	while (++i < bdll->len)
	{
		len += ft_strlen(p->e);
		p = p->r;
	}
	free(a->tkn[a->ab]._);
	a->tkn[a->ab]._ = (t_i8 *) malloc(sizeof(t_i8) * len--);
	return (len);
}

static void	cpy(t_a *a, t_i8 *path, t_bdll *bdll)
{
	t_node	*p;
	t_i32	i;
	t_i32	j;
	t_i32	path_len;

	p = bdll->hd;
	i = -1;
	j = 0;
	path_len = ft_strlen(path);
	while (++i < bdll->len)
	{
		ft_memcpy(a->tkn[a->ab]._ + j, path, path_len);
		j += path_len;
		ft_memcpy(a->tkn[a->ab]._ + j, p->e, ft_strlen(p->e));
		j += ft_strlen(p->e);
		a->tkn[a->ab]._[j++] = ' ';
		p = p->r;
	}
	a->tkn[a->ab]._[--j] = '\0';
}
