/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:57:25 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:12:12 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

t_u64	ft_fact(t_u64 n)
{
	if (!n)
		return (1);
	else
		return (n * ft_fact(n - 1));
}

t_f64	ft_pow(t_f64 n, t_u64 indices)
{
	if (!indices)
		return (1);
	else
		return (n * ft_pow(n, indices - 1));
}

t_u64	ft_fibo(t_u64 idx)
{
	t_u64	arr[2];
	t_u64	seq;

	arr[0] = 0;
	arr[1] = 1;
	seq = 1;
	if (idx < 2)
		return (arr[idx]);
	while (++seq <= idx)
		arr[seq & 1] = arr[0] + arr[1];
	return (arr[!(seq & 1)]);
}

t_f64	ft_sqrt(t_f64 n)
{
	t_f64	l;
	t_f64	r;
	t_f64	med;
	t_f64	prev;

	l = 0;
	r = 1ull << 32;
	prev = 0;
	while (1)
	{
		med = (l + r) / 2;
		if (prev == med)
			return (med);
		else if (med * med < n)
			l = med;
		else if (med * med > n)
			r = med;
		prev = med;
	}
}

t_i32	ft_isprime(t_u64 n)
{
	t_u64	sqrt;

	if (n < 2)
		return (0);
	sqrt = ft_sqrt(n);
	while (sqrt >= 2)
		if (n % sqrt-- == 0)
			return (0);
	return (1);
}
