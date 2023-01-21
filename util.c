/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:16:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/22 01:02:38 by tkong            ###   ########.fr       */
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

void	output(t_db *db, t_i32 out, t_i32 err)
{
	t_i32	i;
	t_i32	j;

	i = -1;
	j = 0;
	while (++i < db->buf_len)
	{
		if (db->buf[i] == STDOUT__)
		{
			write(out, db->buf + j, i - j);
			j = i + 1;
		}
		else if (db->buf[i] == STDERR__)
		{
			write(err, db->buf + j, i - j);
			j = i + 1;
		}
	}
	db->buf_len = 0;
}

void	untool(t_db *db)
{
	while (db->tool_len--)
		free(db->tool[db->tool_len].res);
	db->tool_len++;
}
