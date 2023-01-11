/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vali_mix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:59:03 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:37:54 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_i32	check_mix_minus(t_elem *info)
{
	(void) info;
	return (1);
}

t_i32	check_mix_plus(t_elem *info)
{
	return (!(info->spec & (SPEC_U | SPEC_X | SPEC_X_UP
				| SPEC_C | SPEC_S | SPEC_P)));
}

t_i32	check_mix_space(t_elem *info)
{
	return (!(info->spec & (SPEC_U | SPEC_X | SPEC_X_UP
				| SPEC_C | SPEC_S | SPEC_P)));
}

t_i32	check_mix_sharp(t_elem *info)
{
	return (info->spec & (SPEC_O | SPEC_X | SPEC_X_UP
			| SPEC_PERCENT));
}

t_i32	check_mix_zero(t_elem *info)
{
	return (!(info->spec & (SPEC_C | SPEC_S | SPEC_P | SPEC_N)));
}
