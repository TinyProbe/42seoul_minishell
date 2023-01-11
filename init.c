/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:07:44 by tkong             #+#    #+#             */
/*   Updated: 2023/01/11 17:38:34 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	init(t_db *db)
{
	db->proc_len = ft_strcpy(db->proc, "minish");
	db->cmd = NULL;
	db->cmd_len = 0;
	getcwd(db->cwd, CWD_MAX);
	db->cwd_len = ft_strlen(db->cwd);
	db->sigstat = PROCCMD;
	sigtoggle(db);
}
