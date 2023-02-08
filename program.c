/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:51:05 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 03:03:11 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	subsh2(t_a *a);

void	program(t_a *a)
{
	if (a->cmd_l)
		subsh(a);
	else if (a->ac && !ft_strcmp(a->av[0], "echo"))
		echo(a);
	else if (a->ac && !ft_strcmp(a->av[0], "pwd"))
		pwd(a);
	else if (a->ac && a->av[0][0] == '(')
		subsh2(a);
	else
		file_exe(a);
}

static void	subsh2(t_a *a)
{
	if (a->ac > 1)
		a->errn = ERR_FORMAT;
	error(a);
	a->cmd_l = ft_strlen(a->av[0]) - 2;
	ft_memcpy(a->cmd, a->av[0] + 1, a->cmd_l);
	a->cmd[a->cmd_l] = '\0';
	subsh(a);
}
