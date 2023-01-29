/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:20:13 by tkong             #+#    #+#             */
/*   Updated: 2023/01/29 17:20:19 by tkong            ###   ########.fr       */
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

t_i32	ft_strdel(t_i8 *dst, const t_i8 *set)
{
	t_u8	code[CODE_SIZE];
	t_i32	i;
	t_i32	j;

	ft_bzero(code, CODE_SIZE);
	i = -1;
	while (set[++i])
		code[(t_i32) set[i]] = TRUE;
	i = 0;
	j = -1;
	while (dst[++j])
		if (!code[(t_i32) dst[j]])
			dst[i++] = dst[j];
	dst[i] = '\0';
	return (i);
}
