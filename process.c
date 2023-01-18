/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:06:55 by tkong             #+#    #+#             */
/*   Updated: 2023/01/19 02:00:27 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	process(t_db *db)
{
	t_i32	fd[4];
	pid_t	pid;

	pipe(fd + 0);
	pipe(fd + 2);
	pid = fork();
	if (pid)
		parent(db, fd, pid);
	else
		child(db, fd);
}
