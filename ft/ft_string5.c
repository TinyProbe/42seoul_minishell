/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:20:13 by tkong             #+#    #+#             */
/*   Updated: 2023/01/22 00:08:20 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

size_t	ft_strcpy(t_i8 *dst, const t_i8 *src)
{
	size_t	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (i);
}

t_i8	*ft_strslice(const t_i8 *s1, t_i32 begin, t_i32 end)
{
	t_isize	n;
	void	*res;

	n = end - begin;
	res = malloc(n + 1);
	if (res)
		((char *) ft_memcpy(res, s1 + begin, n))[n] = '\0';
	return (res);
}

t_i32	ft_strdel(t_i8 *dst, t_i8 const *set)
{
	t_u8	code[CODE_SIZE];
	t_i32	l;
	t_i32	r;

	ft_bzero((void *) code, CODE_SIZE);
	while (*set)
		code[(t_i32) *set++] = 1;
	l = 0;
	r = 0;
	while (dst[r])
		if (code[dst[r]])
			++r;
		else
			dst[l++] = dst[r++];
	dst[l] = '\0';
	return (l);
}
