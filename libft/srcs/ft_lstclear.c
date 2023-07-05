/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:02:27 by adi-nata          #+#    #+#             */
/*   Updated: 2022/11/02 23:20:10 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l;

	if (!lst)
		return ;
	if (!*lst)
		return ;
	if (!*del)
		return ;
	while (*lst)
	{
		l = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = l;
	}
	*lst = 0;
}
