/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:50:13 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/08 12:01:53 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next = NULL;
	char		*tok;

	if (str == NULL)
		str = next;
	while (*str && ft_strchr(delim, *str))
		str++;
	if (*str == '\0')
	{
		next = NULL;
		return (NULL);
	}
	tok = str;
	while (*str && !ft_strchr(delim, *str))
		str++;
	if (*str != '\0')
	{
		*str = '\0';
		tok = str + 1;
	}
	else
		next = NULL;
	return (tok);
}
