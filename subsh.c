/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:02:01 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 16:02:47 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_z *z);

void	subsh(t_z *z)
{
	write(z->fd[STDOUT__], "1\n", 2);
	init(z);
	write(z->fd[STDOUT__], "2\n", 2);
	check(z);
	write(z->fd[STDOUT__], "3\n", 2);
	token(z);
	write(z->fd[STDOUT__], "4\n", 2);
	valid(z);
	write(z->fd[STDOUT__], "5\n", 2);
	execute(z);
	write(z->fd[STDOUT__], "6\n", 2);
}

static void	init(t_z *z)
{
	untoken(z);
	unrepl(z);
	z->ac = 0;
	z->ab = 0;
	z->ae = 0;
	z->ri_len = 0;
	z->ro_len = 0;
	z->conj = CONJ_NONE;
}
