/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:04:53 by adi-nata          #+#    #+#             */
/*   Updated: 2022/10/11 16:04:54 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <string.h>
//#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			while (big[i + j] == little[j] && (i + j) < len)
			{
				if (little[j + 1] == '\0')
					return ((char *)&big[i]);
				j++;
			}
		}
		i++;
	}
	if (big[i] == '\0' || i > len)
		return (NULL);
	return (0);
}

/*int main(void)
{   
    //1
     char s[] = "say hello to my hl little friend";
     char ss[] = "lo";
     printf("1: %s\n", ft_strnstr(s, ss, 10));
    //2
     char s5[] = "say hello to my hl little friend";
    char ss5[] = "hl";
     printf("2: %s\n", ft_strnstr(s5, ss5, 20));
    
    // //3
    // char sa[] = "say hello to my hl little friend";
    // char ssa[] = "s";
    // printf("3: %s\n", ft_strnstr(sa, ssa, 0));
    
    //4
     char sw[] = "say hello to my hl little friend";
     char ssw[] = "d";
     printf("4: %s\n", ft_strnstr(sw, ssw, 32));
    // //5
    // char swq[] = "say hello to my hl little friend";
    // char sswq[] = "";
    // printf("5: %s\n", ft_strnstr(swq, sswq, 10));
    
    // //6
    // char sw1[] = "say hello to my hl little friend";
    // char ssw1[] = " ";
    // printf("6: %s\n", ft_strnstr(sw1, ssw1, 4));
    // //7
    // char sw13[] = "say hello to my hl little friend";
    // char ssw13[] = "'\0'";
    // printf("7: %s\n", ft_strnstr(sw13, ssw13, 20));
    // //8
    // char sw13s[] = "say hello to my hl little friend";
    // char ssw13s[] = "dsa";
    // printf("8: %s\n", ft_strnstr(sw13s, ssw13s, 6));
    return (0);
}*/

/*int main()
{
	const char *big = "aloah";
	const char *little = "loa";
	
	const char *bbig = "aloah";
	const char *llittle = "loa";
	
	char *s = ft_strnstr(big, little, 10);
	char *ss = strnstr(bbig, llittle, 10);
	
	printf("mio: %s\n", s);
	printf("loro: %s", ss);
}*/
