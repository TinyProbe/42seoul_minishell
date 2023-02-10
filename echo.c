/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:52:14 by tkong             #+#    #+#             */
/*   Updated: 2023/02/09 04:38:46 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_i32	_cpy(t_a *a, t_i8 *s, t_i32 i);
static void		_out(t_a *a, t_i8 *s, t_i32 len);

void	echo(t_a *a)
{
	t_i8	s[100000];
	t_i32	len;
	t_i32	i;
	t_bool	eol;

	len = 0;
	i = 1;
	eol = TRUE;
	a->proc_l += ft_strcpy(a->proc + a->proc_l, "echo: ");
	if (a->ac > 1 && !ft_strcmp(a->av[1], "-n") && ++i)
		eol = FALSE;
	len = _cpy(a, s, i - 1);
	if (eol)
		s[len++] = '\n';
	_out(a, s, len);
	a->proc_l -= ft_strlen("echo: ");
}

static t_i32	_cpy(t_a *a, t_i8 *s, t_i32 i)
{
	t_i32	len;
	t_i32	tmp;

	len = 0;
	while (++i < a->ac)
	{
		tmp = ft_strlen(a->av[i]);
		ft_memcpy(s + len, a->av[i], tmp);
		len += tmp;
		s[len++] = ' ';
	}
	return (ft_max(0, --len));
}

static void	_out(t_a *a, t_i8 *s, t_i32 len)
{
	write(a->fd[STDOUT__], s, len);
	if (a->ro_l == 0)
		endout(a, STDOUT__);
}
