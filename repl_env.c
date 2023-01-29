/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:01:19 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 14:43:57 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_z *z);

void	repl_env(t_z *z)
{
	t_i32	n;
	t_i8	*tmp;

	if (z->cmd[z->repl[z->repl_len].l + 1] == '?')
	{
		z->repl[z->repl_len]._ = ft_itoa(z->rtn);
		z->repl[z->repl_len].type = TYPE_ENV_RTN;
	}
	else
	{
		n = z->repl[z->repl_len].r - z->repl[z->repl_len].l - 1;
		tmp = ft_memcpy(malloc(sizeof(t_i8) * n + 1),
				z->cmd + z->repl[z->repl_len].l + 1, n);
		tmp[n] = '\0';
		z->repl[z->repl_len]._ = getenv(tmp);
		free(tmp);
		if (z->repl[z->repl_len]._ == NULL)
			z->repl[z->repl_len]._ = "\0";
		z->repl[z->repl_len].type = TYPE_ENV;
	}
	z->repl[z->repl_len].len = ft_strlen(z->repl[z->repl_len]._);
	init(z);
}

static void	init(t_z *z)
{
	z->repl_len++;
	z->repl[z->repl_len].l = z->repl[z->repl_len - 1].l;
	z->repl[z->repl_len].r = z->repl[z->repl_len - 1].r;
	z->repl[z->repl_len].last = -1;
	z->repl[z->repl_len].type = TYPE_NONE;
	z->repl[z->repl_len]._ = NULL;
	z->repl[z->repl_len].len = 0;
}
