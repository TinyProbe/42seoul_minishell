/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:57:29 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 06:38:17 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

t_i32	ft_tolower(t_i32 c)
{
	if (c < 0 || c > 255)
		return (0);
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

t_i32	ft_toupper(t_i32 c)
{
	if (c < 0 || c > 255)
		return (0);
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}

t_i32	ft_stoi(const t_i8 *str)
{
	t_i32	sign;
	t_i64	res;

	sign = 1;
	res = 0;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
		res = (res * 10) + (*str++ - '0');
	return (res * sign);
}

t_i8	*ft_itoa(t_i32 n)
{
	t_i8	buf[20];
	t_i8	*dst;
	t_i32	i;

	if (!n)
		return ((t_i8 *) ft_memcpy(malloc(2), "0", 2));
	i = 0;
	if (n < 0)
		buf[i++] = '-';
	while (n)
	{
		buf[i++] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	buf[i] = '\0';
	ft_reverse(buf, buf[0] == '-', i, sizeof(t_i8));
	dst = (t_i8 *) malloc(i + 1);
	if (!dst)
		return (dst);
	return ((t_i8 *) ft_memcpy(dst, buf, i + 1));
}
