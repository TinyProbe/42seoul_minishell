/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   self.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:29:10 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 03:45:59 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_i32	self(t_a *a)
{
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
	return (0);
}
