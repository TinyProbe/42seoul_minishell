/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:05:59 by tkong             #+#    #+#             */
/*   Updated: 2023/01/11 17:49:52 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	sigtoggle(t_db *db)
{
	if (db->sigstat == WAITCMD)
	{
		db->sigstat = PROCCMD;
		signal(SIGINT, );
		signal(SIGTERM, );
		signal(SIGQUIT, );
	}
	else if (db->sigstat == PROCCMD)
	{
		db->sigstat = WAITCMD;
		signal(SIGINT, sigint);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		perror("minish: sigtoggle error.");
}

void	sigint(int sig)
{
	pid_t	pid;

	(void) sig;
	write(1, MINISH_PROMPT, ft_strlen(MINISH_PROMPT));
	write(1, rl_line_buffer, ft_strlen(rl_line_buffer));
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", FALSE);
	rl_redisplay();
	pid = fork();
	if (!pid)
		exit(1);
	waitpid(pid, NULL, 0);
}
