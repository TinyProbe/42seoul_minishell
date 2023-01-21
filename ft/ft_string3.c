/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:57:18 by tkong             #+#    #+#             */
/*   Updated: 2023/01/21 22:03:17 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

t_i8	*ft_strdup(const t_i8 *s1)
{
	size_t	size;
	void	*res;

	size = ft_strlen(s1) + 1;
	res = malloc(size);
	if (res)
		return ((t_i8 *) ft_memcpy(res, s1, size));
	return (res);
}

t_i8	*ft_strndup(const t_i8 *s1, size_t n)
{
	void	*res;

	res = malloc(n + 1);
	if (res)
		((char *) ft_memcpy(res, s1, n))[n] = '\0';
	return (res);
}

t_i8	*ft_strjoin(t_i8 const *s1, t_i8 const *s2)
{
	size_t	len1;
	size_t	len2;
	t_i8	*dst;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dst = (t_i8 *) malloc(len1 + len2 + 1);
	if (!dst)
		return (dst);
	ft_memcpy(dst, s1, len1 + 1);
	ft_memcpy(dst + len1, s2, len2 + 1);
	return (dst);
}

t_i8	*ft_substr(t_i8 const *s, t_u32 start, size_t len)
{
	t_i8	*dst;
	size_t	len_s;

	len_s = ft_strlen(s);
	if (start >= len_s)
		return ((t_i8 *) ft_calloc(1, 1));
	len = ft_min(len, (t_i64) len_s - start);
	dst = (t_i8 *) malloc(len + 1);
	if (!dst)
		return (dst);
	ft_memcpy(dst, s + start, len);
	dst[len] = '\0';
	return (dst);
}

t_i8	*ft_strtrim(t_i8 const *s1, t_i8 const *set)
{
	t_u8	code[CODE_SIZE];
	t_i32	begin;
	t_i32	end;

	ft_bzero((void *) code, CODE_SIZE);
	while (*set)
		code[(t_i32) *(set++)] = 1;
	begin = -1;
	while (s1[++begin])
		if (!code[(t_i32) s1[begin]])
			break ;
	end = ft_strlen(s1);
	while (end--)
		if (!code[(t_i32) s1[end]])
			break ;
	if (begin > end)
		return ((t_i8 *) ft_calloc(1, 1));
	return (ft_substr(s1, begin, (end + 1) - begin));
}
