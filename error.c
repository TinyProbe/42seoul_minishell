/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:33 by tkong             #+#    #+#             */
/*   Updated: 2023/01/19 16:06:44 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	error(t_db *db)
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
	if (db->fd[STDERR__] != STDERR__)
		exit(db->errno);
	db->errno = 0;
	db->errarg = NULL;
}
