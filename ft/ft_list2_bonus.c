/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:56:34 by tkong             #+#    #+#             */
/*   Updated: 2022/10/28 09:58:00 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = (t_list *) malloc(sizeof(t_list));
	if (!elem)
		return (elem);
	elem->content = content;
	elem->next = (t_list *) 0;
	return (elem);
}

t_i32	ft_lstsize(t_list *lst)
{
	t_i32	len;

	len = 0;
	while (lst)
	{
		++len;
		lst = lst->next;
	}
	return (len);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst2;
	t_list	*cur;

	lst2 = ft_lstnew(f(lst->content));
	lst = lst->next;
	cur = lst2;
	if (lst2)
	{
		while (lst)
		{
			cur->next = ft_lstnew(f(lst->content));
			cur = cur->next;
			lst = lst->next;
			if (cur)
				continue ;
			ft_lstclear(&lst2, del);
			break ;
		}
	}
	return (lst2);
}
