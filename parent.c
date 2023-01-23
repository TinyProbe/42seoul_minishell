/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:01:20 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 01:22:19 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	setparent(t_db *db, t_i32 *fd);
static void	clearparent(t_db *db, t_i32 *fd);
static void	exitsh(t_db *db);

void	parent(t_db *db, t_i32 *fd, pid_t pid)
{
	setparent(db, fd);
	waitpid(pid, &(db->rtn), 0);
	db->buf_len = read(db->fd[STDIN__], db->buf, BUF_MAX);
	clearparent(db, fd);
	if (db->rtn == EXIT)
		exitsh(db);
}

static void	setparent(t_db *db, t_i32 *fd)
{
	db->fd[STDIN__] = fd[0];
	close(fd[1]);
	if (db->conj == CONJ_OR)
	{
		output(db, fd[3], db->fd[STDERR__]);
		close(fd[2]);
		close(fd[3]);
	}
}

static void	clearparent(t_db *db, t_i32 *fd)
{
	db->fd[STDIN__] = STDIN__;
	close(fd[0]);
	if (db->conj != CONJ_OR)
	{
		close(fd[2]);
		close(fd[3]);
	}
}

static void	exitsh(t_db *db)
{
	output(db, db->fd[STDOUT__], db->fd[STDERR__]);
	if (db->fd[STDERR__] != STDERR__)
		exit(db->rtn);
	else
		exit(0);
}
