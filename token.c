/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:03 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 16:32:15 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void		manufact(t_z *z, t_i8 *tkn, t_i32 *i);
static void		seperate(t_z *z, t_i8 *tkn, t_i32 *i);
static t_bool	iswith(t_z *z, t_i8 cur, t_i8 nxt);

void	token(t_z *z)
{
	t_i8	tkn[CMD_MAX];
	t_i32	i[2];

	manufact(z, tkn, i);
}

static void	manufact(t_z *z, t_i8 *tkn, t_i32 *i)
{
	i[0] = -1;
	while (TRUE)
	{
		i[1] = -1;
		while (++i[0] < z->len && ft_isspace(z->cmd[i[0]]))
			;
		if (i[0] >= z->len)
			break ;
		seperate(z, tkn, i);
	}
}

static void	seperate(t_z *z, t_i8 *tkn, t_i32 *i)
{
	while (TRUE)
	{
		tkn[++i[1]] = z->cmd[i[0]];
		if (z->cmd[i[0]] == '(' || z->cmd[i[0]] == ')')
			bracket(z, z->cmd, i[0]);
		else if (z->cmd[i[0]] == '\'')
			quote(z);
		else if (z->cmd[i[0]] == '"')
			claw(z);
		if (++i[0] >= z->len || !iswith(z, tkn[i[1]], z->cmd[i[0]]))
			break;
	}
	z->tkn[z->tkn_len]._ = ft_strndup(tkn, ++i[1]);
	z->tkn[z->tkn_len++].len = i[1];
	--i[0];
}

static t_bool	iswith(t_z *z, t_i8 cur, t_i8 nxt)
{
	if (z->stk_len)
		return (TRUE);
	if (((cur == '&' || cur == '|' || cur == '<'
					|| cur == '>' || cur == ';') && cur != nxt)
			|| ((nxt == '&' || nxt == '|' || nxt == '<'
					|| nxt == '>' || nxt == ';') && cur != nxt)
			|| ft_isspace(nxt))
		return (FALSE);
	return (TRUE);
}
