/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:57:16 by tkong             #+#    #+#             */
/*   Updated: 2022/12/07 16:08:18 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

t_i32	ft_strncmp(const t_i8 *s1, const t_i8 *s2, size_t n)
{
	n = ft_min(n, ft_strlen(s1) + 1);
	n = ft_min(n, ft_strlen(s2) + 1);
	return (ft_memcmp(s1, s2, n));
}

size_t	ft_strlcpy(t_i8 *dst, const t_i8 *src, size_t size)
{
	size_t	len;
	size_t	n;

	len = ft_strlen(src);
	if (!size)
		return (len);
	n = len;
	if (n > size - 1)
		n = size - 1;
	ft_memcpy(dst, src, n);
	dst[n] = '\0';
	return (len);
}

size_t	ft_strlcat(t_i8 *dst, const t_i8 *src, size_t size)
{
	t_u64	p[2];
	size_t	len[2];
	size_t	n;

	len[0] = ft_strlen(dst);
	len[1] = ft_strlen(src);
	p[0] = (t_u64) dst + len[0];
	p[1] = (t_u64) src;
	if (len[0] >= size)
		return (len[1] + size);
	n = size - (len[0] + 1);
	if (n > len[1])
		n = len[1];
	while (n--)
		*(t_u8 *) p[0]++ = *(t_u8 *) p[1]++;
	*(t_u8 *) p[0] = '\0';
	return (len[0] + len[1]);
}

void	ft_striteri(t_i8 *s, void (*f)(t_u32, t_i8 *))
{
	t_i32	i;

	i = -1;
	while (s[++i])
		f((t_u32) i, s + i);
}

t_i8	*ft_strmapi(t_i8 const *s, t_i8 (*f)(t_u32, t_i8))
{
	t_i8	*dst;
	size_t	n;

	n = ft_strlen(s);
	dst = (t_i8 *) malloc(n + 1);
	if (!dst)
		return (dst);
	while (n--)
		dst[n] = f(n, s[n]);
	return (dst);
}
