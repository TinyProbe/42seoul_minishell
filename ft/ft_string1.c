/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:57:14 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 16:11:16 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

size_t	ft_strlen(const t_i8 *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		++len;
	return (len);
}

t_i8	*ft_strchr(const t_i8 *s, t_i32 c)
{
	return ((t_i8 *) ft_memchr(s, c, ft_strlen(s) + 1));
}

t_i8	*ft_strrchr(const t_i8 *s, t_i32 c)
{
	t_u64	p;
	size_t	n;

	n = ft_strlen(s) + 1;
	p = (t_u64) s + n;
	while (n--)
		if (*(t_u8 *)--p == (t_u8) c)
			return ((t_i8 *) p);
	return ((t_i8 *) 0);
}

t_i8	*ft_strnstr(const t_i8 *big, const t_i8 *little, size_t n)
{
	size_t	len[2];
	t_i32	i[2];

	len[0] = ft_strlen(big);
	len[1] = ft_strlen(little);
	if (len[0] > n)
		len[0] = n;
	i[0] = -1;
	while ((size_t)++i[0] + len[1] <= len[0])
	{
		i[1] = -1;
		while ((size_t)++i[1] < len[1])
			if (big[i[0] + i[1]] != little[i[1]])
				break ;
		if ((size_t) i[1] == len[1])
			return ((t_i8 *) big + i[0]);
	}
	return ((t_i8 *) 0);
}

t_i32	ft_strcmp(const t_i8 *s1, const t_i8 *s2)
{
	size_t	n;

	n = ft_strlen(s1) + 1;
	n = ft_min(n, ft_strlen(s2) + 1);
	return (ft_memcmp(s1, s2, n));
}
