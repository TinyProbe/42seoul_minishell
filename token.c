/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:03 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 15:18:05 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void		manufact(t_a *a, t_i8 *tkn, t_i32 *i);
static void		seperate(t_a *a, t_i8 *tkn, t_i32 *i);
static t_bool	iswith(t_a *a, t_i8 cur, t_i8 nxt);

t_i32	token(t_a *a)
{
	t_i8	tkn[CMD_MAX];
	t_i32	i[2];

	manufact(a, tkn, i);
	return (a->errn);
}

static void	manufact(t_a *a, t_i8 *tkn, t_i32 *i)
{
	i[0] = -1;
	while (TRUE)
	{
		i[1] = -1;
		while (++i[0] < a->cmd_l && ft_isspace(a->cmd[i[0]]))
			;
		if (i[0] >= a->cmd_l)
			break ;
		seperate(a, tkn, i);
	}
}

static void	seperate(t_a *a, t_i8 *tkn, t_i32 *i)
{
	while (TRUE)
	{
		tkn[++i[1]] = a->cmd[i[0]];
		if (a->cmd[i[0]] == '(' || a->cmd[i[0]] == ')')
			bracket(a, a->cmd, i[0]);
		else if (a->cmd[i[0]] == '\'')
			quote(a);
		else if (a->cmd[i[0]] == '"')
			claw(a);
		if (++i[0] >= a->cmd_l || !iswith(a, tkn[i[1]], a->cmd[i[0]]))
			break ;
	}
	a->tkn[a->tkn_l]._ = ft_strndup(tkn, ++i[1]);
	a->tkn[a->tkn_l++].len = i[1];
	--i[0];
}

static t_bool	iswith(t_a *a, t_i8 cur, t_i8 nxt)
{
	if (a->stk_l)
		return (TRUE);
	if (((cur == '&' || cur == '|' || cur == '<'
				|| cur == '>' || cur == ';') && cur != nxt)
		|| ((nxt == '&' || nxt == '|' || nxt == '<'
				|| nxt == '>' || nxt == ';') && cur != nxt)
		|| ft_isspace(nxt))
		return (FALSE);
	return (TRUE);
}
