/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:58:44 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 09:59:14 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	apply_prec(t_elem *info)
{
	if (info->prec && !(info->spec & SPEC_S))
	{
		while (info->end - info->begin < info->precis)
			info->res[--(info->begin)] = '0';
		info->flag -= (info->flag & FLAG_ZERO);
	}
}

void	apply_base(t_elem *info)
{
	if (info->flag & FLAG_SHARP)
	{
		if (info->spec & SPEC_O)
			info->res[--(info->begin)] = '0';
		else if (info->spec & (SPEC_X | SPEC_P))
		{
			info->res[--(info->begin)] = 'x';
			info->res[--(info->begin)] = '0';
		}
		else if (info->spec & SPEC_X_UP)
		{
			info->res[--(info->begin)] = 'X';
			info->res[--(info->begin)] = '0';
		}
	}
}

void	apply_wid(t_elem *info)
{
	if (info->flag & FLAG_ZERO)
	{
		if (info->flag & (FLAG_PLUS | FLAG_SPACE) || info->neg)
			info->width--;
		else if (info->flag & FLAG_SHARP)
		{
			info->width--;
			if (info->spec & (SPEC_X | SPEC_X_UP))
				info->width--;
		}
		while (info->end - info->begin < info->width)
			info->res[--(info->begin)] = '0';
		return ;
	}
	if (info->flag & FLAG_MINUS)
		while (info->end - info->begin < info->width)
			info->res[info->end++] = ' ';
	else
		while (info->end - info->begin < info->width)
			info->res[--(info->begin)] = ' ';
}

void	apply_sign(t_elem *info)
{
	if (info->neg)
		info->res[--(info->begin)] = '-';
	else if (info->flag & FLAG_PLUS)
		info->res[--(info->begin)] = '+';
	else if (info->flag & FLAG_SPACE)
		info->res[--(info->begin)] = ' ';
}
