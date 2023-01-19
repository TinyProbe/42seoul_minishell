/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 05:29:50 by tkong             #+#    #+#             */
/*   Updated: 2023/01/20 06:57:12 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	setrange(t_db *db, t_i32 i, t_i32 j);
static void		setcmd(t_db *db, t_i32 i, t_i32 j, t_i32 k);
static void		replace(t_db *db, t_i32 i, t_i32 j);

void	substitution(t_db *db, t_i32 i)
{
	t_i32	len;
	t_i32	j;
	t_i32	k;

	len = ft_strlen(db->tkn[i]);
	j = -1;
	while ()
	{
		//
		k = setrange(db, i, j);
		setcmd(db, i, j, k);
		process(db);
		replace(db, i, j);
	}
}

static t_i32	setrange(t_db *db, t_i32 i, t_i32 j)
{
	return (0);
}

static void	setcmd(t_db *db, t_i32 i, t_i32 j, t_i32 k)
{

}

static void	replace(t_db *db, t_i32 i, t_i32 j)
{

}
