/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:54:12 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 15:17:06 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_i32	check(t_a *a)
{
	t_i32	i;

	i = -1;
	while (++i < a->cmd_l)
	{
		if (a->cmd[i] == '(' || a->cmd[i] == ')')
			bracket(a, a->cmd, i);
		else if (a->cmd[i] == '\'')
			quote(a);
		else if (a->cmd[i] == '"')
			claw(a);
		else if (a->cmd[i] == '\\')
			a->errn = ERR_RESTRICT;
		if (a->errn)
			return (a->errn);
	}
	if (a->stk_l)
		a->errn = ERR_FORMAT;
	return (a->errn);
}

void	bracket(t_a *a, t_i8 *s, t_i32 i)
{
	if (a->stk_l && a->stk[a->stk_l - 1] == '\'')
		return ;
	if (s[i] == '(')
	{
		if ((i > 0 && s[i - 1] == '$')
			|| (!(a->stk_l) || a->stk[a->stk_l - 1] == '('))
			a->stk[a->stk_l++] = '(';
	}
	else
	{
		if (a->stk_l && a->stk[a->stk_l - 1] == '(')
			a->stk_l--;
		else if (!(a->stk_l))
			a->errn = ERR_FORMAT;
	}
}

void	quote(t_a *a)
{
	if (a->stk_l && a->stk[a->stk_l - 1] == '"')
		return ;
	if (a->stk_l && a->stk[a->stk_l - 1] == '\'')
		a->stk_l--;
	else
		a->stk[a->stk_l++] = '\'';
}

void	claw(t_a *a)
{
	if (a->stk_l && a->stk[a->stk_l - 1] == '\'')
		return ;
	if (a->stk_l && a->stk[a->stk_l - 1] == '"')
		a->stk_l--;
	else
		a->stk[a->stk_l++] = '"';
}
