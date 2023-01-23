/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:33:56 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 06:40:45 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	repl_buf(t_db *db);
static void	init(t_db *db);

void	repl_cmd(t_db *db)
{
	db->len = db->repl[db->repl_len].r - db->repl[db->repl_len].l - 3;
	ft_memcpy(db->cmd, db->tkn[db->arg_b]._
			+ db->repl[db->repl_len].l + 2, db->len);
	process(db);
	repl_buf(db);
	db->repl[db->repl_len]._ = ft_memcpy(
			malloc(sizeof(t_i8) * db->buf_len + 1), db->buf, db->buf_len);
	db->repl[db->repl_len]._[db->buf_len] = '\0';
	db->repl[db->repl_len].len = db->buf_len;
	db->repl[db->repl_len].type = TYPE_CMD;
	init(db);
}

static void	repl_buf(t_db *db)
{
	t_i32	i;
	t_i32	j;
	t_i32	k;

	i = -1;
	j = 0;
	k = 0;
	while (++i < db->buf_len)
	{
		if (db->buf[i] == STDOUT__)
		{
			while (j < i)
				db->buf[k++] = db->buf[j++];
			j = i + 1;
		}
		else if (db->buf[i] == STDERR__)
		{
			write(db->fd[STDERR__], db->buf + j, i - j + 1);
			j = i + 1;
		}
	}
	db->buf_len = k;
}

static void	init(t_db *db)
{
	db->repl_len++;
	db->repl[db->repl_len].l = db->repl[db->repl_len - 1].l;
	db->repl[db->repl_len].r = db->repl[db->repl_len - 1].r;
	db->repl[db->repl_len].last = -1;
	db->repl[db->repl_len].type = TYPE_NONE;
	db->repl[db->repl_len]._ = NULL;
	db->repl[db->repl_len].len = 0;
}
