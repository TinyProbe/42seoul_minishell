/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:03:12 by tkong             #+#    #+#             */
/*   Updated: 2023/01/30 12:19:33 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_i8	**split__(t_i8 *s, t_i8 c)
{
	t_i8	*buf[100000];
	t_i32	len;
	t_i32	l;
	t_i32	r;

	len = 0;
	l = 0;
	r = -1;
	while (s[++r])
	{
		if (s[r] == c)
		{
			if (l < r)
				buf[len++] = ft_strndup(s + l, r - l);
			l = r + 1;
		}
	}
	if (l < r)
		buf[len++] = ft_strndup(s + l, r - l);
	buf[len++] = NULL;
	return (ft_memcpy(malloc(sizeof(t_i8 *) * len), buf, sizeof(t_i8 *) * len));
}
