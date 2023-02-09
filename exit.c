/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:52:14 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 03:46:58 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	getrtn__(t_a *a);
static t_i32	check_arg(t_a *a);

void	exit__(t_a *a)
{
	t_i32	rtn;
	t_i32	fd[2];

	pipe(fd);
	setself(a, fd);
	a->proc_l += ft_strcpy(a->proc + a->proc_l, "exit: ");
	rtn = 0;
	if (a->ac > 2)
		a->errn = ERR_TOOMANY;
	else
	{
		if (a->ac > 1)
			rtn = getrtn__(a);
		output(a, a->fd[STDOUT__], a->fd[STDERR__]);
		write(a->fd[STDOUT__], "exit\n", 5);
		endout(a, STDOUT__);
		exit(rtn);
	}
	error(a);
	a->proc_l -= ft_strlen("exit: ");
	recover(a, fd);
}

static t_i32	getrtn__(t_a *a)
{
	t_i32	rtn;

	rtn = check_arg(a);
	if (rtn)
	{
		a->errn = ERR_NUMERIC;
		a->erra = a->av[1];
		error(a);
		rtn %= -2;
	}
	else
		rtn = ft_atoi(a->av[1]);
	return (rtn);
}

static t_i32	check_arg(t_a *a)
{
	t_i32	i;

	i = -1;
	while (a->av[1][++i])
		if (!ft_isdigit(a->av[1][i]))
			return (-1);
	if (ft_atoi(a->av[1]) == -1)
		return (-2);
	return (0);
}
