/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:03:14 by adi-nata          #+#    #+#             */
/*   Updated: 2022/10/24 21:35:10 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*s;
	size_t		n;

	n = ft_strlen(s1) + 1;
	s = (char *)malloc(sizeof(*s) * n);
	if (!s)
		return (NULL);
	return ((char *)ft_memcpy(s, s1, n));
}
