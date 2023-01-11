/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:57:20 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:11:20 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static t_i8		*trim(const t_i8 *s, t_i8 c);
static size_t	split(const t_i8 *trimmed, t_i8 **buf, t_i8 c);

t_i8	**ft_split(t_i8 const *s, t_i8 c)
{
	t_i8	*trimmed;
	t_i8	*buf[100000];
	size_t	num;

	trimmed = trim(s, c);
	if (!trimmed)
		return ((t_i8 **) 0);
	num = split(trimmed, buf, c);
	free(trimmed);
	return (ft_memcpy((t_i8 **) malloc(sizeof(t_i8 *) * (num + 1)), buf,
			sizeof(t_i8 *) * (num + 1)));
}

static t_i8	*trim(const t_i8 *s, t_i8 c)
{
	t_i8	*dst;
	t_i8	set[2];
	t_i32	i[2];

	*(t_u16 *) set = (t_u16) c;
	dst = ft_strtrim(s, set);
	if (!dst)
		return (dst);
	*(t_i64 *) i = (t_i64) 0;
	while (dst[i[0]])
	{
		if (dst[i[0]] == c && dst[i[0] - 1] == c)
			while (dst[i[0]] == c)
				++i[0];
		if (i[0] ^ i[1])
			dst[i[1]] = dst[i[0]];
		++i[0];
		++i[1];
	}
	dst[i[1]] = '\0';
	return (dst);
}

static size_t	split(const t_i8 *trimmed, t_i8 **buf, t_i8 c)
{
	t_u64	p1;
	t_u64	p2;
	size_t	num;

	p1 = (t_u64) trimmed;
	p2 = (t_u64) ft_memchr((t_i8 *) p1, c, ft_strlen((t_i8 *) p1));
	num = 0;
	while (p2)
	{
		buf[num++] = ft_substr((t_i8 *) p1, 0, p2 - p1);
		p1 = p2 + 1;
		p2 = (t_u64) ft_memchr((t_i8 *) p1, c, ft_strlen((t_i8 *) p1));
	}
	if (*(t_i8 *) p1)
		buf[num++] = ft_strdup((t_i8 *) p1);
	buf[num] = (t_i8 *) 0;
	return (num);
}
