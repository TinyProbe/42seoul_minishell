/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:16:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/15 19:12:19 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_i32	recwd(t_db *db)
{
	if (!getcwd(db->cwd, CWD_MAX))
	{
		db->err = ERRNO_LONGCWD;
		return (-1);
	}
	else
		db->cwd_len = ft_strlen(db->cwd);
	return (0);
}
