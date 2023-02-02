/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:52:14 by tkong             #+#    #+#             */
/*   Updated: 2023/02/01 19:27:11 by tkong            ###   ########.fr       */
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
	i = 0;
	eol = TRUE;
	a->proc_l += ft_strcpy(a->proc + a->proc_l, "echo: ");
	while (++i < a->ac && a->av[i][0] == '-')
		if (ft_strchr(a->av[i], 'n'))
			eol = FALSE;
	len = _cpy(a, s, i - 1);
	if (eol)
		s[len++] = '\n';
	_out(a, s, len);
}

static t_i32	_cpy(t_a *a, t_i8 *s, t_i32 i)
{
	t_i32	len;
	t_i32	tmp;

	len = 0;
	while (++i < a->ac)
	{
		if (a->av[i][0] == '-')
		{
			a->errn = ERR_FORMAT;
			a->erra = a->av[i];
			error(a);
		}
		tmp = ft_strlen(a->av[i]);
		ft_memcpy(s + len, a->av[i], tmp);
		len += tmp;
		s[len++] = ' ';
	}
	return (--len);
}

static void	_out(t_a *a, t_i8 *s, t_i32 len)
{
	write(a->fd[STDOUT__], s, len);
	endout(a, STDOUT__);
}
