/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:54:05 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 09:54:12 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static t_buf	*find_buf(t_buf *buf, t_i32 fd);
static t_i32	fill_buf(t_buf *buf);

t_i8	*ft_gnl(t_i32 fd)
{
	static t_buf	buf[MAX_FILE];
	t_i8			str[MAX_LEN];
	t_i32			idx;
	t_buf			*cur;

	idx = 0;
	cur = buf;
	if (fd < 0)
		return (0);
	if (fd)
		cur = find_buf(buf + 1, fd);
	while (1)
	{
		if (cur->idx == cur->len && !fill_buf(cur))
		{
			if (idx)
				return (ft_strndup(str, idx));
			return (0);
		}
		str[idx++] = cur->buf[cur->idx++];
		if (str[idx - 1] == '\n')
			return (ft_strndup(str, idx));
	}
}

static t_buf	*find_buf(t_buf *buf, t_i32 fd)
{
	while (buf->fd && buf->fd != fd)
		++buf;
	buf->fd = fd;
	return (buf);
}

static t_i32	fill_buf(t_buf *buf)
{
	buf->idx = 0;
	buf->len = read(buf->fd, buf->buf, BUFFER_SIZE);
	if (buf->len <= 0)
	{
		buf->idx = buf->len;
		return (0);
	}
	return (1);
}
