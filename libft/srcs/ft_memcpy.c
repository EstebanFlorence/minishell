/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:03:14 by adi-nata          #+#    #+#             */
/*   Updated: 2022/10/11 16:03:14 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/*int main()
{
	char dest[10] = "ehi";
	char src[10] = "addios";
	
	char destp[10] = "ehi";
	char srcp[10] = "addios";
	
	ft_memcpy(dest, src, sizeof(dest));
	memcpy(destp, srcp, sizeof(destp));
	
	printf("loro: %s\nmio: ", destp);
	puts(dest);
}*/
