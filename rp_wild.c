/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rp_wild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:34:07 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 15:15:57 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_bdll	import(DIR *dir, t_i8 *file);
static void		join(t_a *a, t_i8 *path, t_i32 path_l, t_bdll *bdll);

t_i32	rp_wild(t_a *a)
{
	DIR		*dir;
	t_i8	*path;
	t_i8	*file;
	t_bdll	bdll;

	path = getpath(a->cwd, a->tkn[a->ab]._);
	file = getfile(a->tkn[a->ab]._, a->tkn[a->ab].len);
	dir = opendir(path);
	if (!dir)
	{
		free(path);
		free(file);
		a->errn = ERR_FILEPATH;
		a->erra = path;
		return (a->errn);
	}
	bdll = import(dir, file);
	join(a, path, ft_strlen(path), &bdll);
	free(path);
	free(file);
	while (bdll.len)
		free(ft_popb(&bdll));
	return (a->errn);
}

static t_bdll	import(DIR *dir, t_i8 *file)
{
	t_bdll		bdll;
	t_dirent	*dt;

	ft_bzero(&bdll, sizeof(t_bdll));
	dt = readdir(dir);
	while (dt)
	{
		if (isincl(dt->d_name, file))
		{
			ft_pushb(&bdll, ft_memcpy(malloc(sizeof(t_i8) * dt->d_namlen + 1),
					dt->d_name, dt->d_namlen));
			((t_i8 *) ft_back(&bdll))[dt->d_namlen] = '\0';
		}
		dt = readdir(dir);
	}
	closedir(dir);
	return (bdll);
}

static void	join(t_a *a, t_i8 *path, t_i32 path_l, t_bdll *bdll)
{
	t_i8	s[100000];
	t_i32	i;
	t_i32	j;
	t_node	*p;

	free(a->tkn[a->ab]._);
	a->tkn[a->ab]._ = NULL;
	i = -1;
	p = bdll->hd;
	path_l = ft_strlen(path);
	a->ext[a->ext_l].l = a->ac;
	while (++i < bdll->len)
	{
		j = 0;
		ft_memcpy(s + j, path, path_l);
		j += path_l;
		ft_memcpy(s + j, p->e, ft_strlen(p->e));
		j += ft_strlen(p->e);
		a->av[a->ac++] = ft_strndup(s, j);
		p = p->r;
	}
	a->ext[a->ext_l++].r = a->ac;
}
