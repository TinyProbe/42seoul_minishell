/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:51:05 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 17:46:03 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	subsh2(t_z *z);

void	program(t_z *z)
{
	if (z->len)
		subsh(z);
	else if (z->ac && !ft_strcmp(z->av[0], "echo"))
		echo(z);
	else if (z->ac && !ft_strcmp(z->av[0], "cd"))
		cd(z);
	else if (z->ac && !ft_strcmp(z->av[0], "pwd"))
		pwd(z);
	else if (z->ac && !ft_strcmp(z->av[0], "export"))
		export__(z);
	else if (z->ac && !ft_strcmp(z->av[0], "unset"))
		unset(z);
	else if (z->ac && !ft_strcmp(z->av[0], "env"))
		env(z);
	else if (z->ac && !ft_strcmp(z->av[0], "exit"))
		exit__(z);
	else if (z->ac && z->av[0][0] == '(')
		subsh2(z);
	else if (z->ac && z->av[0][0] == '.')
		file_exe(z);
}

static void	subsh2(t_z *z)
{
	if (z->ac > 1)
		z->errno = ERRNO_FORMAT;
	error(z);
	z->len = ft_strlen(z->av[0]) - 2;
	ft_memcpy(z->cmd, z->av[0] + 1, z->len);
	subsh(z);
}
