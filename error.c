/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:33 by tkong             #+#    #+#             */
/*   Updated: 2023/01/15 20:33:08 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	error(t_db *db)
{
	ft_putstr_fd(db->proc, STDERR__);
	ft_putstr_fd(": ", STDERR__);
	ft_putstr_fd(db->errmsg[db->errno], STDERR__);
	ft_putstr_fd("\n", STDERR__);
	if (db->lv)
		exit(db->errno);
	db->errno = 0;
}
