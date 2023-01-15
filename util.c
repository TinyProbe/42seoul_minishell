/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:16:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/15 23:47:00 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	recwd(t_db *db)
{
	if (!getcwd(db->cwd, CWD_MAX))
	{
		db->errno = ERRNO_LONGCWD;
		error(db);
	}
	else
		db->cwd_len = ft_strlen(db->cwd);
}

void	pipelink(int *fd, int dir)
{
	close(fd[((dir || 0) + 1) % 2]);
	dup2(fd[dir || 0], dir);
}
