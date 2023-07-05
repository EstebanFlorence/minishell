/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:03:19 by adi-nata          #+#    #+#             */
/*   Updated: 2022/10/21 22:24:41 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*s;
	char		*d;
	size_t		i;

	i = 0;
	s = (const char *) src;
	d = (char *) dst;
	if (d > s)
	{
		while (i < len)
		{
			d[len - i -1] = s[len - i - 1];
			i++;
		}
	}
	else
		ft_memcpy (d, s, len);
	return (d);
}

/*int main()
{
    char str1[100] = "Porco";
    char str2[5] = "dio";
  
    puts("mio str1 prima di memmove:");
    puts(str1);

    ft_memmove(str1, str2, sizeof(str2));
  
    puts("str1 dopo memmove:");
    puts(str1);
    
    char str3[100] = "Porco";
    char str4[5] = "dio";
  
    puts("loro str3 prima memmove:");
    puts(str3);

    memmove(str3, str4, sizeof(str4));
  
    puts("str3 dopo memmove:");
    puts(str3);
  
    return 0;
}*/
