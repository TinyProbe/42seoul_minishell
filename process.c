/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 20:06:55 by tkong             #+#    #+#             */
/*   Updated: 2023/01/16 01:43:49 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	parent(t_db *db, t_i32 *out_fd, t_i32 *err_fd, pid_t pid);
static void	child(t_db *db, t_i32 *out_fd, t_i32 *err_fd, void (*ftr)(t_db *));
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
		parent(db, out_fd, err_fd, pid);
	else
		child(db, out_fd, err_fd, ftr);
}

static void	parent(t_db *db, t_i32 *out_fd, t_i32 *err_fd, pid_t pid)
{
	t_i32	rtn;

	waitpid(pid, &rtn, 0);
	pipelink(out_fd, STDIN__);
	db->out_len = read(STDIN__, db->out, OUT_MAX);
	pipelink(err_fd, STDIN__);
	db->err_len = read(STDIN__, db->err, ERR_MAX);
}

static void	child(t_db *db, t_i32 *out_fd, t_i32 *err_fd, void (*ftr)(t_db *))
{
	pipelink(out_fd, STDOUT__);
	pipelink(err_fd, STDERR__);
	setchild(db, ftr);
	ftr(db);
	exit(0);
}

static void	setchild(t_db *db, void (*ftr)(t_db *))
{
	db->lv++;
	untoken(db);
}
