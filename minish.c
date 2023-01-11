/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:11:45 by tkong             #+#    #+#             */
/*   Updated: 2023/01/11 17:36:48 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	minish(t_db *db)
{
	while (TRUE)
	{
		db->cmd = readline(MINISH_PROMPT);
		if (db->cmd == NULL)
		{
			ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
			ft_putstr_fd("\033[8C", STDOUT_FILENO);
			write(1, "exit\n", 5);
			exit(0);
		}
		db->cmd_len = ft_strlen(db->cmd);
		add_history(db->cmd);
		if (!ft_strcmp(db->cmd, "exit"))
			break ;
		sigtoggle(db);
		subsh(db);
		sigtoggle(db);
		free(db->cmd);
	}
}
