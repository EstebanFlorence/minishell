/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:04:13 by adi-nata          #+#    #+#             */
/*   Updated: 2022/10/20 02:48:05 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}

/*int main()
{
	const char *s = "gesuBastardo";
	const char *ss = "gesuBastardo";
	char a = 'B';
	char aa = 'B';
	
	printf("%s\n", ft_strchr(s, a));
	printf("%s", strchr(ss, aa));
}*/
