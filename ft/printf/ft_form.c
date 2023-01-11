/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_form.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:58:49 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:30:20 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_i32	scan_flag(const t_i8 *form, t_i32 idx, t_elem *info)
{
	t_i32	tmp;

	tmp = is_flag(form[idx++]);
	while (tmp)
	{
		info->flag |= tmp;
		tmp = is_flag(form[idx++]);
	}
	return (idx - 1);
}

t_i32	scan_wid(const t_i8 *form, t_i32 idx, t_elem *info)
{
	t_i32	tmp;

	tmp = is_wid(form[idx++]);
	while (tmp)
	{
		info->wid |= tmp;
		if (tmp & WID_NUM)
			info->width = info->width * 10 + (form[idx - 1] - '0');
		tmp = is_wid(form[idx++]);
	}
	return (idx - 1);
}

t_i32	scan_prec(const t_i8 *form, t_i32 idx, t_elem *info)
{
	t_i32	tmp;

	tmp = is_prec(form[idx++]);
	if (tmp & PREC_DOT)
	{
		info->prec |= tmp;
		tmp = is_prec(form[idx++]);
		while (tmp)
		{
			info->prec |= tmp;
			if (tmp & PREC_NUM)
				info->precis = info->precis * 10 + (form[idx - 1] - '0');
			tmp = is_prec(form[idx++]);
		}
	}
	return (idx - 1);
}

t_i32	scan_len(const t_i8 *form, t_i32 idx, t_elem *info)
{
	t_i32	tmp;

	tmp = is_len(form[idx++]);
	while (tmp)
	{
		info->len += tmp;
		tmp = is_len(form[idx++]);
	}
	return (idx - 1);
}

t_i32	scan_spec(const t_i8 *form, t_i32 idx, t_elem *info)
{
	t_i32	tmp;

	tmp = is_spec(form[idx++]);
	if (tmp)
		info->spec |= tmp;
	return (idx);
}
