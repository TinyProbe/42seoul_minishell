/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:20 by tkong             #+#    #+#             */
/*   Updated: 2023/01/19 05:15:53 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_i32	exec(t_db *db)
{
	t_i32	i;
	t_i8	out;

	i = -1;
	out = STDOUT__;
	while (++i < db->tkn_len)
	{
		write(db->fd[STDOUT__], db->tkn[i], ft_strlen(db->tkn[i]));
		write(db->fd[STDOUT__], "\n", 1);
		write(db->fd[STDOUT__], &out, 1);
	}
	return (0);
}
