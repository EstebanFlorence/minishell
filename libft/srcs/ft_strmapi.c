/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:03:17 by adi-nata          #+#    #+#             */
/*   Updated: 2022/11/01 12:59:18 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*d;

	i = 0;
	d = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (s == NULL)
		return (NULL);
	while (s != NULL)
	{
		d[i] = f(i, d[i]);
		i++;
	}
	d[i] = '\0';
	return (d);
}
