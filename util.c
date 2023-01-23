/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:16:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 06:02:42 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	recwd(t_db *db)
{
	if (!getcwd(db->cwd, CWD_MAX))
		db->errno = ERRNO_LONGCWD;
	else
		db->cwd_len = ft_strlen(db->cwd);
	error(db);
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
			write(out, db->buf + j, i - j + (out != STDOUT__));
			j = i + 1;
		}
		else if (db->buf[i] == STDERR__)
		{
			write(err, db->buf + j, i - j + (err != STDERR__));
			j = i + 1;
		}
	}
	db->buf_len = 0;
}

void	untoken(t_db *db)
{
	while (db->tkn_len--)
		free(db->tkn[db->tkn_len]._);
	db->tkn_len++;
}

void	unrepl(t_db *db)
{
	while (db->repl_len--)
		if (db->repl[db->repl_len].type != TYPE_ENV)
			free(db->repl[db->repl_len]._);
	db->repl_len++;
}
