/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 08:04:16 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 14:49:35 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	calclen(t_z *z, t_i8 *path, t_bdll *bdll);
static void		cpy(t_z *z, t_i8 *path, t_bdll *bdll);

void	join(t_z *z, t_i8 *path, t_bdll *bdll)
{
	calclen(z, path, bdll);
	cpy(z, path, bdll);
}

static t_i32 calclen(t_z *z, t_i8 *path, t_bdll *bdll)
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
	free(z->tkn[z->ab]._);
	z->tkn[z->ab]._ = (t_i8 *) malloc(sizeof(t_i8) * len--);
	return (len);
}

static void	cpy(t_z *z, t_i8 *path, t_bdll *bdll)
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
		ft_memcpy(z->tkn[z->ab]._ + j, path, path_len);
		j += path_len;
		ft_memcpy(z->tkn[z->ab]._ + j, p->e, ft_strlen(p->e));
		j += ft_strlen(p->e);
		z->tkn[z->ab]._[j++] = ' ';
		p = p->r;
	}
	z->tkn[z->ab]._[--j] = '\0';
}
