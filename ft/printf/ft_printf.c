/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:59:00 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:28:35 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_i32	ft_printf(const t_i8 *format, ...)
{
	va_list	ap;
	t_i32	rtn;

	va_start(ap, format);
	rtn = ft_vfprintf(format, ap);
	va_end(ap);
	return (rtn);
}
