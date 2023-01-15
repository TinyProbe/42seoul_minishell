/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:03 by tkong             #+#    #+#             */
/*   Updated: 2023/01/15 19:12:19 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void		manufact(t_db *db, t_i8 *tkn, t_i32 *i);
static void		seperate(t_db *db, t_i8 *tkn, t_i32 *i);
static t_bool	iswith(t_db *db, t_i8 cur, t_i8 nxt);

t_i32	token(t_db *db)
{
	t_i8	tkn[CMD_MAX];
	t_i32	i[2];

	manufact(db, tkn, i);
	return (0);
}

void	untoken(t_db *db)
{
	while (db->tkn_len--)
		free(db->tkn[db->tkn_len]);
	db->tkn_len++;
}

static void	manufact(t_db *db, t_i8 *tkn, t_i32 *i)
{
	i[0] = -1;
	while (TRUE)
	{
		i[1] = -1;
		while (++i[0] < db->len && ft_isspace(db->cmd[i[0]]))
			;
		if (i[0] >= db->len)
			break ;
		seperate(db, tkn, i);
	}
}

static void	seperate(t_db *db, t_i8 *tkn, t_i32 *i)
{
	while (TRUE)
	{
		tkn[++i[1]] = db->cmd[i[0]];
		if (db->cmd[i[0]] == '(' || db->cmd[i[0]] == ')')
			bracket(db, i[0]);
		else if (db->cmd[i[0]] == '\'')
			quote(db);
		else if (db->cmd[i[0]] == '"')
			claw(db);
		if (++i[0] >= db->len || !iswith(db, tkn[i[1]], db->cmd[i[0]]))
			break;
	}
	db->tkn[db->tkn_len++] = ft_strndup(tkn, ++i[1]);
	--i[0];
}

static t_bool	iswith(t_db *db, t_i8 cur, t_i8 nxt)
{
	if (db->stk_len)
		return (TRUE);
	if (((cur == '&' || cur == '|' || cur == '<'
					|| cur == '>' || cur == ';') && cur != nxt)
			|| ((nxt == '&' || nxt == '|' || nxt == '<'
					|| nxt == '>' || nxt == ';') && cur != nxt)
			|| ft_isspace(nxt))
		return (FALSE);
	return (TRUE);
}
