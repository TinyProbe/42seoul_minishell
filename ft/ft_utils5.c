/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:57:31 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:13:10 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

#define DIGIT	1
#define SPACE	2

static t_i32	iswhat(t_i32 c);
static t_i32	getsign(const t_i8 **pstr);
static size_t	dglen(const t_i8 *s);

t_i32	ft_atoi(const t_i8 *str)
{
	t_i32		sign;
	size_t		dlen;
	const t_i8	*max = "9223372036854775808";

	while (*str && (iswhat(*str) & SPACE))
		++str;
	sign = getsign(&str);
	dlen = dglen(str);
	if (sign == 1)
		max = "9223372036854775807";
	if (dlen > 19 || (dlen == 19 && ft_strncmp(str, max, dlen) > 0))
		return (~(sign >> 1));
	return (ft_stoi(str) * sign);
}

static t_i32	iswhat(t_i32 c)
{
	t_u8	c1;

	c1 = c;
	c = 0;
	if (ft_isdigit(c1))
		c += DIGIT;
	if (ft_isspace(c1))
		c += SPACE;
	return (c);
}

static t_i32	getsign(const t_i8 **pstr)
{
	if (**pstr == '-')
	{
		++(*pstr);
		return (-1);
	}
	else if (**pstr == '+')
		++(*pstr);
	return (1);
}

static size_t	dglen(const t_i8 *s)
{
	size_t	len;

	len = 0;
	while (s[len] && (iswhat(s[len]) & DIGIT))
		++len;
	return (len);
}
