/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:26:37 by adi-nata          #+#    #+#             */
/*   Updated: 2023/03/06 23:27:08 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_lstnew(int nb)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack) * 1);
	if (new == NULL)
		return (NULL);
	new->nbr = nb;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
