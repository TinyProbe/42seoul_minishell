/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:33 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 02:48:31 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	display(t_db *db);

void	error(t_db *db)
{
	if (db->errno == ERRNO_NONE)
		return ;
	display(db);
	if (db->fd[STDERR__] != STDERR__)
		exit(db->errno);
	db->rtn = db->errno;
	db->errno = 0;
	db->errarg = NULL;
}

static void	display(t_db *db)
{
	t_i8	err;

	err = STDERR__;
	write(db->fd[STDERR__], db->proc, db->proc_len);
	if (db->errarg)
	{
		write(db->fd[STDERR__], db->errarg, ft_strlen(db->errarg));
		write(db->fd[STDERR__], ": ", 2);
	}
	write(db->fd[STDERR__], db->errmsg[db->errno],
			ft_strlen(db->errmsg[db->errno]));
	write(db->fd[STDERR__], "\n", 1);
	write(db->fd[STDERR__], &err, 1);
}
