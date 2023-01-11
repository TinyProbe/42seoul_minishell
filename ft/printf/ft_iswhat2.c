/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhat2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:58:58 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 09:59:20 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_i32	is_spec_part1(t_i32 c)
{
	if (c == 'd' || c == 'i')
		return (SPEC_D_OR_I);
	if (c == 'u')
		return (SPEC_U);
	if (c == 'o')
		return (SPEC_O);
	if (c == 'x')
		return (SPEC_X);
	if (c == 'X')
		return (SPEC_X_UP);
	if (c == 'f')
		return (SPEC_F);
	if (c == 'F')
		return (SPEC_F_UP);
	if (c == 'e')
		return (SPEC_E);
	if (c == 'E')
		return (SPEC_E_UP);
	return (0);
}

t_i32	is_spec_part2(t_i32 c)
{
	if (c == 'g')
		return (SPEC_G);
	if (c == 'G')
		return (SPEC_G_UP);
	if (c == 'a')
		return (SPEC_A);
	if (c == 'A')
		return (SPEC_A_UP);
	if (c == 'c')
		return (SPEC_C);
	if (c == 's')
		return (SPEC_S);
	if (c == 'p')
		return (SPEC_P);
	if (c == 'n')
		return (SPEC_N);
	if (c == '%')
		return (SPEC_PERCENT);
	return (0);
}
