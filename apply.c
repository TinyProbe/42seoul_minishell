/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:04:37 by tkong             #+#    #+#             */
/*   Updated: 2023/01/20 05:32:21 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_i32	apply(t_db *db, t_i32 i)
{
	substitution(db, i);
	if ((db->tkn[i][0] == '|' || db->tkn[i][0] == '&') && db->ftr)
		return (-1);
	if (db->tkn[i][0] == '|')
		db->ctrl = CTRL_OR + (ft_strlen(db->tkn[i]) == 2);
	else if (db->tkn[i][0] == '&')
		db->ctrl = CTRL_ANDAND;
	else if (db->tkn[i][0] == '(')
		f1(db, i);
	else if (db->tkn[i][0] == '<' || db->tkn[i][0] == '>')
		f2(db, i);
	else
		f3(db, i);
	return (0);
}
