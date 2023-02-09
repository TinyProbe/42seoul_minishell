/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 07:26:08 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 03:18:55 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void		file_run(t_a *a);
static void		path_run(t_a *a);
static t_i32	path_run2(t_a *a, t_i8 **paths);

void	file_exe(t_a *a)
{
	if (ft_strchr(a->av[0], '/'))
		file_run(a);
	else
		path_run(a);
}

static void	file_run(t_a *a)
{
	t_i32	fd;

	fd = open(a->av[0], O_RDONLY);
	if (fd == -1)
	{
		a->errn = ERR_FILEPATH;
		a->erra = a->av[0];
		error(a);
	}
	else
	{
		close(fd);
		dup2(a->fd[STDIN__], STDIN__);
		if (a->dup2_cnt)
			dup2(a->fd[STDOUT__], STDOUT__);
		execve(a->av[0], a->av, environ);
	}
}

static void	path_run(t_a *a)
{
	t_i8	**paths;
	t_i8	*path;
	t_i32	i;

	path = getenv__(a, "PATH");
	paths = NULL;
	if (path)
		paths = ft_split(path, ':');
	if (!path || path_run2(a, paths))
	{
		a->errn = ERR_FILEPATH;
		a->erra = a->av[0];
		error(a);
	}
	if (paths)
	{
		i = -1;
		while (paths[++i])
			free(paths[i]);
		free(paths);
	}
}

static t_i32	path_run2(t_a *a, t_i8 **paths)
{
	t_i8	path[100000];
	t_i32	len;
	t_i32	i;
	t_i32	fd;

	i = -1;
	while (paths[++i])
	{
		len = ft_strcpy(path, paths[i]);
		path[len++] = '/';
		len += ft_strcpy(path + len, a->av[0]);
		fd = open(path, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			dup2(a->fd[STDIN__], STDIN__);
			if (a->dup2_cnt)
				dup2(a->fd[STDOUT__], STDOUT__);
			execve(path, a->av, environ);
			return (0);
		}
		close(fd);
	}
	return (-1);
}
