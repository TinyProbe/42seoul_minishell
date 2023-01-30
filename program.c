/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:51:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 13:50:26 by tkong            ###   ########.fr       */
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
	else if (a->ac && !ft_strcmp(a->av[0], "cd"))
		cd(a);
	else if (a->ac && !ft_strcmp(a->av[0], "pwd"))
		pwd(a);
	else if (a->ac && !ft_strcmp(a->av[0], "export"))
		export__(a);
	else if (a->ac && !ft_strcmp(a->av[0], "unset"))
		unset(a);
	else if (a->ac && !ft_strcmp(a->av[0], "env"))
		env(a);
	else if (a->ac && !ft_strcmp(a->av[0], "exit"))
		exit__(a);
	else if (a->ac && a->av[0][0] == '(')
		subsh2(a);
	else if (a->ac && a->av[0][0] == '.')
		file_exe(a);
}

static void	subsh2(t_a *a)
{
	if (a->ac > 1)
		a->errno = ERRNO_FORMAT;
	error(a);
	a->cmd_l = ft_strlen(a->av[0]) - 2;
	ft_memcpy(a->cmd, a->av[0] + 1, a->cmd_l);
	subsh(a);
}
