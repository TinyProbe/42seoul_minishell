/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:54:12 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 14:43:57 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	check(t_z *z)
{
	t_i32	i;

	i = -1;
	while (++i < z->len)
	{
		if (z->cmd[i] == '(' || z->cmd[i] == ')')
			bracket(z, z->cmd, i);
		else if (z->cmd[i] == '\'')
			quote(z);
		else if (z->cmd[i] == '"')
			claw(z);
		else if (z->cmd[i] == '\\')
			z->errno = ERRNO_RESTRICT;
		if (z->errno)
			error(z);
	}
	if (z->stk_len)
		z->errno = ERRNO_FORMAT;
	error(z);
}

void	bracket(t_z *z, t_i8 *s, t_i32 i)
{
	if (z->stk_len && z->stk[z->stk_len - 1] == '\'')
		return ;
	if (s[i] == '(')
	{
		if ((i > 0 && s[i - 1] == '$')
				|| (!(z->stk_len) || z->stk[z->stk_len - 1] == '('))
			z->stk[z->stk_len++] = '(';
	}
	else
	{
		if (z->stk_len && z->stk[z->stk_len - 1] == '(')
			z->stk_len--;
		else if (!(z->stk_len))
			z->errno = ERRNO_FORMAT;
	}
}

void	quote(t_z *z)
{
	if (z->stk_len && z->stk[z->stk_len - 1] == '"')
		return ;
	if (z->stk_len && z->stk[z->stk_len - 1] == '\'')
		z->stk_len--;
	else
		z->stk[z->stk_len++] = '\'';
}

void	claw(t_z *z)
{
	if (z->stk_len && z->stk[z->stk_len - 1] == '\'')
		return ;
	if (z->stk_len && z->stk[z->stk_len - 1] == '"')
		z->stk_len--;
	else
		z->stk[z->stk_len++] = '"';
}
