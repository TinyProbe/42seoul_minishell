/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:01:19 by tkong             #+#    #+#             */
/*   Updated: 2023/01/23 06:01:26 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_db *db);

void	repl_env(t_db *db)
{
	t_i32	n;
	t_i8	*tmp;

	if (db->cmd[db->repl[db->repl_len].l + 1] == '?')
	{
		db->repl[db->repl_len]._ = ft_itoa(db->rtn);
		db->repl[db->repl_len].type = TYPE_ENV_RTN;
	}
	else
	{
		n = db->repl[db->repl_len].r - db->repl[db->repl_len].l - 1;
		tmp = ft_memcpy(malloc(sizeof(t_i8) * n + 1),
				db->cmd + db->repl[db->repl_len].l + 1, n);
		tmp[n] = '\0';
		db->repl[db->repl_len]._ = getenv(tmp);
		free(tmp);
		if (db->repl[db->repl_len]._ == NULL)
			db->repl[db->repl_len]._ = "\0";
		db->repl[db->repl_len].type = TYPE_ENV;
	}
	db->repl[db->repl_len].len = ft_strlen(db->repl[db->repl_len]._);
	init(db);
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
