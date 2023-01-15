/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:11:45 by tkong             #+#    #+#             */
/*   Updated: 2023/01/14 19:11:05 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	cmdread(t_db *db);
static t_i32	cmdcpy(t_db *db, t_i8 *cmd);

void	minish(t_db *db)
{
	while (TRUE)
	{
		if (cmdread(db))
			continue ;
		sigtoggle(db);
		subsh(db);
		sigtoggle(db);
	}
}

static t_i32	cmdread(t_db *db)
{
	t_i8	*cmd;

	cmd = readline(PROMPT);
	if (!cmd)
	{
		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[8C", STDOUT_FILENO);
		ft_putstr_fd("exit\n", STDOUT__);
		exit(0);
	}
	else if (!ft_strcmp(cmd, "exit"))
		exit(0);
	return cmdcpy(db, cmd);
}

static t_i32	cmdcpy(t_db *db, t_i8 *cmd)
{
	add_history(cmd);
	db->len = ft_strlen(cmd);
	if (db->len >= CMD_MAX)
	{
		db->err = ERRNO_LONGCMD;
		error(db);
		free(cmd);
		return (-1);
	}
	ft_memcpy(db->cmd, cmd, db->len);
	free(cmd);
	return (0);
}
