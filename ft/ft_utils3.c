/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:57:27 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 10:12:29 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static void	ft_swap_half(void *a, void *b, size_t siz);

void	ft_swap(void *a, void *b, size_t siz)
{
	if (a == b)
		return ;
	if (siz == sizeof(t_u8))
	{
		*(t_u8 *) a ^= *(t_u8 *) b;
		*(t_u8 *) b ^= *(t_u8 *) a;
		*(t_u8 *) a ^= *(t_u8 *) b;
	}
	else if (siz == sizeof(t_u16))
	{
		*(t_u16 *) a ^= *(t_u16 *) b;
		*(t_u16 *) b ^= *(t_u16 *) a;
		*(t_u16 *) a ^= *(t_u16 *) b;
	}
	else
		ft_swap_half(a, b, siz);
}

static void	ft_swap_half(void *a, void *b, size_t siz)
{
	if (siz == sizeof(t_u32))
	{
		*(t_u32 *) a ^= *(t_u32 *) b;
		*(t_u32 *) b ^= *(t_u32 *) a;
		*(t_u32 *) a ^= *(t_u32 *) b;
	}
	else if (siz == sizeof(t_u64))
	{
		*(t_u64 *) a ^= *(t_u64 *) b;
		*(t_u64 *) b ^= *(t_u64 *) a;
		*(t_u64 *) a ^= *(t_u64 *) b;
	}
}

void	ft_reverse(void *arr, t_i32 begin, t_i32 end, size_t siz)
{
	if (siz == sizeof(t_u8))
		while (begin < --end)
			ft_swap((t_u8 *) arr + begin++, (t_u8 *) arr + end, siz);
	else if (siz == sizeof(t_u16))
		while (begin < --end)
			ft_swap((t_u16 *) arr + begin++, (t_u16 *) arr + end, siz);
	else if (siz == sizeof(t_u32))
		while (begin < --end)
			ft_swap((t_u32 *) arr + begin++, (t_u32 *) arr + end, siz);
	else if (siz == sizeof(t_u64))
		while (begin < --end)
			ft_swap((t_u64 *) arr + begin++, (t_u64 *) arr + end, siz);
}
