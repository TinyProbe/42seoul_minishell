/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:59:01 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:31:07 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	stores(t_elem *info, const t_i8 *s);

void	set_arg_value(va_list ap, t_elem *info)
{
	if (info->spec & SPEC_D_OR_I)
		itodec(info, va_arg(ap, t_i32));
	else if (info->spec & SPEC_U)
		utodec(info, va_arg(ap, t_u32));
	else if (info->spec & SPEC_X)
		ulltohex(info, va_arg(ap, t_u32), 0);
	else if (info->spec & SPEC_X_UP)
		ulltohex(info, va_arg(ap, t_u32), 1);
	else if (info->spec & SPEC_C)
		info->res[info->end++] = va_arg(ap, t_i32);
	else if (info->spec & SPEC_S)
		stores(info, va_arg(ap, const t_i8 *));
	else if (info->spec & SPEC_P)
		ptohex(info, va_arg(ap, void *));
	else if (info->spec & SPEC_PERCENT)
		info->res[info->end++] = '%';
}

static void	stores(t_elem *info, const t_i8 *s)
{
	const t_i8 *const	null = "(null)";
	t_i32				idx;
	t_i32				precis;

	idx = 0;
	precis = 0;
	if (s)
		while (s[idx] && (!info->prec || precis++ < info->precis))
			info->res[info->end++] = s[idx++];
	else
		while (null[idx] && (!info->prec || precis++ < info->precis))
			info->res[info->end++] = null[idx++];
}
