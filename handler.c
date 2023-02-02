/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:05:59 by tkong             #+#    #+#             */
/*   Updated: 2023/02/02 12:59:59 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	sigtoggle(t_a *a)
{
	if (a->sigstat == SIGS_WAITCMD)
	{
		a->sigstat = SIGS_PROCCMD;
		signal(SIGINT, sigint);
		signal(SIGTERM, sigterm);
		signal(SIGQUIT, sigquit);
	}
	else if (a->sigstat == SIGS_PROCCMD)
	{
		a->sigstat = SIGS_WAITCMD;
		signal(SIGINT, sigint_rl);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	sigint_rl(t_i32 sig)
{
	(void) sig;
	write(STDOUT__, g_a->lln, g_a->lln_l);
	ft_putstr_fd(PROMPT, STDOUT__);
	ft_putstr_fd(rl_line_buffer, STDOUT__);
	ft_putstr_fd("  \n", STDOUT__);
	rl_on_new_line();
	rl_replace_line("", FALSE);
	rl_redisplay();
	g_a->lln_l = 0;
	g_a->rtn = 1;
	waitpid(0, NULL, 0);
}

void	sigint(t_i32 sig)
{
	(void) sig;
}

void	sigterm(t_i32 sig)
{
	(void) sig;
}

void	sigquit(t_i32 sig)
{
	(void) sig;
}
