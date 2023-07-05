/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:03:07 by adi-nata          #+#    #+#             */
/*   Updated: 2022/10/11 16:03:08 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == ((unsigned char)c))
			return (((unsigned char *)s) + i);
		i++;
	}
	return (NULL);
}

/*int main()
{
	char *s = "Aoh";
	//char *ss = "Aoh";
	char c = 'h';
	//char cc = 'h';
	
	ft_memchr(s, c, 4);
	//memchr(ss, cc, 4);
	
	puts(s);
	//puts(ss);
	
	
}*/
