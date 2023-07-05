/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:51:09 by adi-nata          #+#    #+#             */
/*   Updated: 2023/01/03 11:47:11 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*trim(const char *s1, char *d, size_t e, size_t s)
{
	size_t	i;

	i = 0;
	if (d == NULL || !d)
		return (NULL);
	while (s <= e)
	{
		d[i] = s1[s];
		i++;
		s++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	s;
	size_t	e;
	char	*d;

	if (!set || ft_strlen(set) <= 0)
		return (NULL);
	if (!s1 || ft_strlen(s1) <= 0)
		return (NULL);
	s = 0;
	e = ft_strlen(s1) - 1;
	while (s1[s] && ft_strchr(set, s1[s]))
		s++;
	while (ft_strchr(set, s1[e]))
		e--;
	d = (char *)malloc(sizeof(char) * (e - s + 1) + 1);
	trim(s1, d, e, s);
	return (d);
}
