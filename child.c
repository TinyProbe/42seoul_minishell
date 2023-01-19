/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:02:43 by tkong             #+#    #+#             */
/*   Updated: 2023/01/19 15:42:45 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	setchild(t_db *db, t_i32 *fd);

void	child(t_db *db, t_i32 *fd)
{
	setchild(db, fd);
	db->ftr(db);
	output(db, db->fd[STDOUT__], db->fd[STDERR__]);
	exit(0);
}

static void	setchild(t_db *db, t_i32 *fd)
{
	db->fd[STDOUT__] = fd[1];
	db->fd[STDERR__] = fd[1];
	close(fd[0]);
	if (db->ctrl == CTRL_OR)
	{
		db->fd[STDIN__] = fd[2];
		close(fd[3]);
	}
	redirect(db);
	if (db->ftr != subsh)
	{
		db->proc_len += ft_strcpy(db->proc + db->proc_len, db->av[0]);
		db->proc_len += ft_strcpy(db->proc + db->proc_len, ": ");
	}
	db->buf_len = 0;
}
