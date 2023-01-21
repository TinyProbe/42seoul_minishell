/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:02:43 by tkong             #+#    #+#             */
/*   Updated: 2023/01/21 19:43:25 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	setchild(t_db *db, t_i32 *fd);

void	child(t_db *db, t_i32 *fd)
{
	setchild(db, fd);
	program(db);
	output(db, db->fd[STDOUT__], db->fd[STDERR__]);
	exit(0);
}

static void	setchild(t_db *db, t_i32 *fd)
{
	db->fd[STDOUT__] = fd[1];
	db->fd[STDERR__] = fd[1];
	close(fd[0]);
	if (db->conj == CONJ_OR)
	{
		db->fd[STDIN__] = fd[2];
		close(fd[3]);
	}
	redirect(db);
	db->buf_len = 0;
}
