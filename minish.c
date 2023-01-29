/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:11:45 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 17:55:55 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	cmdread(t_z *z);
static t_i32	cmdcpy(t_z *z, t_i8 *cmd);

void	minish(t_z *z)
{
	while (TRUE)
	{
		if (cmdread(z))
			continue ;
		sigtoggle(z);
		subsh(z);
		output(z, z->fd[STDOUT__], z->fd[STDERR__]);
		sigtoggle(z);
	}
}

static t_i32	cmdread(t_z *z)
{
	t_i8	*cmd;

	cmd = readline(PROMPT);
	if (!cmd)
	{
		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[8C", STDOUT_FILENO);
		ft_putstr_fd("exit\n", z->fd[STDOUT__]);
		exit(0);
	}
	return cmdcpy(z, cmd);
}

static t_i32	cmdcpy(t_z *z, t_i8 *cmd)
{
	add_history(cmd);
	z->len = ft_strlen(cmd);
	if (z->len >= CMD_MAX)
	{
		z->errno = ERRNO_LONGCMD;
		error(z);
		free(cmd);
		return (-1);
	}
	ft_memcpy(z->cmd, cmd, z->len);
	free(cmd);
	return (0);
}
