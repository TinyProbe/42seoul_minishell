/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:29:10 by tkong             #+#    #+#             */
/*   Updated: 2023/02/08 22:29:30 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	recover(t_a *a);

t_i32	self(t_a *a)
{
	// use pipe to outputs on self.
	if (a->ac && !ft_strcmp(a->av[0], "cd"))
		cd(a);
	else if (a->ac && !ft_strcmp(a->av[0], "env"))
		env(a);
	else if (a->ac && !ft_strcmp(a->av[0], "export"))
		export__(a);
	else if (a->ac && !ft_strcmp(a->av[0], "unset"))
		unset(a);
	else if (a->ac && !ft_strcmp(a->av[0], "exit"))
		exit__(a);
	else
		return (-1);
	recover(a);
	return (0);
}

static void	recover(t_a *a)
{
	if (a->fd[STDIN__] != a->fd_old[STDIN__])
	{
		close(a->fd[STDIN__]);
		a->fd[STDIN__] = a->fd_old[STDIN__];
	}
	if (a->fd[STDOUT__] != a->fd_old[STDOUT__])
	{
		close(a->fd[STDOUT__]);
		a->fd[STDOUT__] = a->fd_old[STDIN__];
	}
}
