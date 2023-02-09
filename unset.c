/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:52:14 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 03:47:08 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	unset(t_a *a)
{
	t_i32	i;
	t_i32	fd[2];

	pipe(fd);
	setself(a, fd);
	a->proc_l += ft_strcpy(a->proc + a->proc_l, "unset: ");
	if (check_env2(a, 0, 0))
		error(a);
	else
	{
		i = 0;
		while (++i < a->ac)
		{
			del_env(&(a->env), a->av[i]);
			del_env(&(a->exp), a->av[i]);
		}
	}
	a->proc_l -= ft_strlen("unset: ");
	recover(a, fd);
}
