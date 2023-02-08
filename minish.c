/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:11:45 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 18:05:11 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	cmdread(t_a *a);
static t_i32	cmdcpy(t_a *a, t_i8 *cmd);

void	minish(t_a *a)
{
	while (TRUE)
	{
		if (cmdread(a))
			continue ;
		sigtoggle(a);
		subsh(a);
		output(a, a->fd[STDOUT__], a->fd[STDERR__]);
		sigtoggle(a);
	}
}

static t_i32	cmdread(t_a *a)
{
	t_i8	*cmd;

	cmd = readline(PROMPT);
	if (!cmd)
	{
		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[8C", STDOUT_FILENO);
		ft_putstr_fd("exit\n", a->fd[STDOUT__]);
		exit(0);
	}
	return (cmdcpy(a, cmd));
}

static t_i32	cmdcpy(t_a *a, t_i8 *cmd)
{
	a->cmd_l = ft_strlen(cmd);
	if (a->cmd_l >= CMD_MAX)
	{
		a->errn = ERR_LONGCMD;
		error(a);
		free(cmd);
		return (-1);
	}
	if (a->cmd_l)
		add_history(cmd);
	ft_memcpy(a->cmd, cmd, a->cmd_l + 1);
	free(cmd);
	return (0);
}
