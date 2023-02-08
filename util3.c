/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:54:24 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 15:14:17 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_bool	deadln(t_i8 *cur, t_i8 *file, t_i8 **frags);
static t_bool	dfs(t_i8 *cur, t_i8 **frags, t_i32 i);

t_bool	isincl(t_i8 *cur, t_i8 *file)
{
	t_i8	**frags;
	t_bool	rtn;
	t_i32	i;

	frags = ft_split(file, '*');
	rtn = (deadln(cur, file, frags) && dfs(cur, frags, 0));
	i = -1;
	while (frags[++i])
		free(frags[i]);
	free(frags);
	return (rtn);
}

static t_bool	deadln(t_i8 *cur, t_i8 *file, t_i8 **frags)
{
	t_i32	last;

	last = -1;
	while (frags[++last])
		;
	if (file[0] != '*' && ft_strncmp(cur, frags[0], ft_strlen(frags[0])))
		return (FALSE);
	if (file[ft_strlen(file) - 1] != '*'
		&& ft_strncmp(cur + (ft_strlen(cur) - ft_strlen(frags[last - 1])),
			frags[last - 1], ft_strlen(frags[last - 1])))
		return (FALSE);
	return (TRUE);
}

static t_bool	dfs(t_i8 *cur, t_i8 **frags, t_i32 i)
{
	while (frags[i])
	{
		cur = ft_strnstr(cur, frags[i], ft_strlen(cur));
		if (cur++ && dfs(cur, frags, i + 1))
			return (TRUE);
		else
			return (FALSE);
	}
	return (TRUE);
}

void	unext(t_a *a)
{
	while (a->ext_l--)
		while (a->ext[a->ext_l].l < a->ext[a->ext_l].r)
			free(a->av[a->ext[a->ext_l].l++]);
	a->ext_l++;
}
