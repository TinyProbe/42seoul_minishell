/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:34:02 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 12:42:26 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i8	*abspath(t_i8 *arg);
static t_i8	*relpath(t_i8 *cwd, t_i8 *arg);
static void	joinarg(t_i8 *res, t_i8 *arg, t_i32 i);

t_i8	*getpath(t_i8 *cwd, t_i8 *arg)
{
	if (!arg)
		return (NULL);
	if (arg[0] == '/')
		return (abspath(arg));
	else
		return (relpath(cwd, arg));
}

static t_i8	*abspath(t_i8 *arg)
{
	t_i8	*res;
	t_i32	i;

	i = ft_strlen(arg);
	while (arg[--i] != '/')
		;
	++i;
	res = ft_memcpy(malloc(sizeof(t_i8) * i + 1), arg, i);
	res[i] = '\0';
	return (res);
}

static t_i8	*relpath(t_i8 *cwd, t_i8 *arg)
{
	t_i8	*res;
	t_i32	i;
	t_i32	j;

	i = ft_strlen(cwd);
	j = ft_strlen(arg);
	res = ft_memcpy(
			malloc(sizeof(t_i8) * (i + j) + 2), cwd, i);
	res[i++] = '/';
	joinarg(res, arg, i);
	return (res);
}

static void	joinarg(t_i8 *res, t_i8 *arg, t_i32 i)
{
	t_i8	word[1024];
	t_i32	j;
	t_i32	k;

	j = -1;
	k = 0;
	while (arg[++j])
	{
		word[k++] = arg[j];
		if (arg[j] == '/')
		{
			word[k] = '\0';
			if (!ft_strcmp(word, "../"))
				while (--i > 0 && res[i - 1] != '/')
					;
			else if (ft_strcmp(word, "./"))
			{
				ft_memcpy(res + i, word, k);
				i += k;
			}
			k = 0;
		}
	}
	res[i] = '\0';
}

t_i8	*getfile(t_i8 *arg, t_i32 len)
{
	t_i8	*res;
	t_i32	i;

	if (!arg)
		return (NULL);
	i = len;
	while (--i >= 0 && arg[i] != '/')
		;
	len -= ++i;
	res = ft_memcpy(malloc(sizeof(t_i8) * len + 1), arg + i, len);
	res[len] = '\0';
	return (res);
}
