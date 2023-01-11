/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:59:05 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:38:10 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_i32	check_flag(t_elem *info)
{
	if (!(info->flag ^ (FLAG_MINUS | FLAG_ZERO)))
		return (0);
	if (!(info->flag ^ (FLAG_PLUS | FLAG_SPACE)))
		return (0);
	if (info->spec & (SPEC_O | SPEC_X | SPEC_X_UP)
		&& (info->flag & (FLAG_PLUS | FLAG_SPACE)))
		return (0);
	if (info->flag & FLAG_MINUS && !check_mix_minus(info))
		return (0);
	if (info->flag & FLAG_PLUS && !check_mix_plus(info))
		return (0);
	if (info->flag & FLAG_SPACE && !check_mix_space(info))
		return (0);
	if (info->flag & FLAG_SHARP && !check_mix_sharp(info))
		return (0);
	if (info->flag & FLAG_ZERO && !check_mix_zero(info))
		return (0);
	return (1);
}

t_i32	check_wid(t_elem *info)
{
	return (info->wid ^ (WID_NUM | WID_STAR));
}

t_i32	check_prec(t_elem *info)
{
	if (!(info->prec ^ (PREC_NUM | PREC_STAR)))
		return (0);
	if (info->prec & (PREC_NUM | PREC_STAR)
		&& info->spec & (SPEC_C | SPEC_P | SPEC_N))
		return (0);
	return (1);
}

t_i32	check_len(t_elem *info)
{
	return (!info->len);
}

t_i32	check_spec(t_elem *info)
{
	return (info->spec);
}
