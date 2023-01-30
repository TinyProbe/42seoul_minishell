/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_wild.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:34:07 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 13:58:35 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_bdll	import(t_a *a, t_i8 *path, t_i8 *file);

void	rp_wild(t_a *a)
{
	t_i8	*path;
	t_i8	*file;
	t_bdll	bdll;

	path = getpath(a->cwd, a->tkn[a->ab]._);
	file = getfile(a->tkn[a->ab]._, a->tkn[a->ab].len);
	bdll = import(a, path, file);
	join(a, path, &bdll);
	free(path);
	free(file);
}

static t_bdll	import(t_a *a, t_i8 *path, t_i8 *file)
{
	t_bdll		bdll;
	DIR			*dir;
	t_dirent	*dt;

	ft_bzero(&bdll, sizeof(t_bdll));
	dir = opendir(path);
	if (!dir)
	{
		a->errno = ERRNO_FILEPATH;
		a->errarg = path;
		error(a);
	}
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
