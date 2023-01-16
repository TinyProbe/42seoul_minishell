/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:06:55 by tkong             #+#    #+#             */
/*   Updated: 2023/01/17 04:13:06 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	parent(t_db *db, pid_t pid);
static void	join(t_db *db, t_i32 fd);
static void	child(t_db *db, void (*ftr)(t_db *));
static void	setchild(t_db *db, void (*ftr)(t_db *));

void	process(t_db *db, void (*ftr)(t_db *))
{
	t_i32	out_fd[2];
	t_i32	err_fd[2];
	pid_t	pid;

	pipe(out_fd);
	pipe(err_fd);
	pid = fork();
	if (pid)
	{
		close(out_fd[1]);
		close(err_fd[1]);
		db->io = out_fd[0];
		db->ie = err_fd[0];
		parent(db, pid);
	}
	else
	{
		close(out_fd[0]);
		close(err_fd[0]);
		db->o = out_fd[1];
		db->e = err_fd[1];
		child(db, ftr);
	}
}

static void	parent(t_db *db, pid_t pid)
{
	while (TRUE)
	{
		if (waitpid(pid, &(db->rtn), WNOHANG))
			break ;
		db->buf_len = read(db->io, db->buf, BUF_MAX);
		join(db, db->io);
		db->buf_len = read(db->ie, db->buf, BUF_MAX);
		join(db, db->ie);
	}
}

static void	join(t_db *db, t_i32 fd)
{
	if (db->buf_len <= 0)
		return ;

}

static void	child(t_db *db, void (*ftr)(t_db *))
{
	setchild(db, ftr);
	ftr(db);
	exit(0);
}

static void	setchild(t_db *db, void (*ftr)(t_db *))
{
	db->lv++;
	untoken(db);
}
