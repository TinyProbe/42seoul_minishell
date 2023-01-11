/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:57:05 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:07:36 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static void		unit_merge_sort(t_u32 **buf, t_i32 seq, size_t len);
static t_i32	replace_buf(t_u32 **buf, t_i32 seq, size_t len, t_i32 *i);

void	ft_sort_u32(t_u32 *arr, t_i32 begin, t_i32 end)
{
	t_u32	*buf[2];
	t_i32	seq;
	size_t	len;

	len = end - begin;
	buf[0] = (t_u32 *) malloc(sizeof(t_u32) * len);
	buf[1] = (t_u32 *) malloc(sizeof(t_u32) * len);
	if (!buf[0] || !buf[1])
		return ;
	ft_memcpy(buf[0], arr + begin, sizeof(t_u32) * len);
	seq = 0;
	while ((1 << seq) < (t_i32) len)
		unit_merge_sort(buf, seq++, len);
	ft_memcpy(arr + begin, buf[seq & 1], sizeof(t_u32) * len);
	free(buf[0]);
	free(buf[1]);
}

static void	unit_merge_sort(t_u32 **buf, t_i32 seq, size_t len)
{
	t_i32	i[4];

	i[2] = 0;
	i[3] = 0;
	while (i[2] < (t_i32) len)
	{
		i[0] = i[2];
		i[1] = i[2] + (1 << seq);
		while (1)
			if (replace_buf(buf, seq, len, i))
				break ;
		i[2] += (1 << seq) * 2;
	}
}

static t_i32	replace_buf(t_u32 **buf, t_i32 seq, size_t len, t_i32 *i)
{
	if (i[0] < ft_min(i[2] + (1 << seq), (t_i32) len))
	{
		if (i[1] < ft_min(i[2] + (1 << seq) * 2, (t_i32) len))
		{
			if (buf[seq & 1][i[0]] < buf[seq & 1][i[1]])
				buf[!(seq & 1)][i[3]++] = buf[seq & 1][i[0]++];
			else
				buf[!(seq & 1)][i[3]++] = buf[seq & 1][i[1]++];
		}
		else
			buf[!(seq & 1)][i[3]++] = buf[seq & 1][i[0]++];
	}
	else if (i[1] < ft_min(i[2] + (1 << seq) * 2, (t_i32) len))
		buf[!(seq & 1)][i[3]++] = buf[seq & 1][i[1]++];
	else
		return (-1);
	return (0);
}
