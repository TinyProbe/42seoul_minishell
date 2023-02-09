/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:06:55 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 02:56:03 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_i32	process(t_a *a)
{
	t_i32	fd[4];
	pid_t	pid;

	pipe(fd + 0);
	pipe(fd + 2);
	pid = fork();
	if (pid)
		parent(a, fd, pid);
	else
		child(a, fd);
	return (0);
}
