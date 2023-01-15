/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:10:33 by tkong             #+#    #+#             */
/*   Updated: 2023/01/15 18:06:49 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	error(t_db *db)
{
	ft_putstr_fd(db->proc, STDOUT__);
	ft_putstr_fd(": ", STDOUT__);
	ft_putstr_fd(db->errmsg[db->err], STDOUT__);
	ft_putstr_fd("\n", STDOUT__);
	if (db->err == ERRNO_LONGCWD)
		exit(db->err);
}
