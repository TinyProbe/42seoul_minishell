/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:57:22 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:11:53 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

t_f64	ft_abs(t_f64 n)
{
	if (n < 0)
		return (-n);
	return (n);
}

t_f64	ft_max(t_f64 a, t_f64 b)
{
	if (a > b)
		return (a);
	return (b);
}

t_f64	ft_min(t_f64 a, t_f64 b)
{
	if (a < b)
		return (a);
	return (b);
}

t_u64	ft_gcd(t_u64 a, t_u64 b)
{
	if (a < b)
		ft_swap(&a, &b, sizeof(t_u64));
	while (b)
	{
		a %= b;
		ft_swap(&a, &b, sizeof(t_u64));
	}
	return (a);
}

t_u64	ft_lcm(t_u64 a, t_u64 b)
{
	return (a * b / ft_gcd(a, b));
}
