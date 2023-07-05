/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:02:14 by adi-nata          #+#    #+#             */
/*   Updated: 2022/10/20 02:50:03 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)str)[i++] = c;
	return (str);
}

/*int main(void)
{
	 char str[100] = "hello";
	 char br[100] = "hello";

	printf("mio: %s\n", str);
	printf("loro: %s\n", br);
	printf("Post funzioni:\n");
 
	ft_memset(str, 'A', 42);
	printf("mio: %s\n", str);
	memset(br, 'A', 42);
	printf("loro: %s\n", br);
}*/
