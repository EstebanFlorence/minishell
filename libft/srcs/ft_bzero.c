/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:42:03 by adi-nata          #+#    #+#             */
/*   Updated: 2022/10/10 22:42:06 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <strings.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = '\0';
}

/*int main()
{
	char s[20] = "ti amo";
	char t[20] = "ti amo";
	
	ft_bzero(s + 2, 3*sizeof(char));
	bzero(t + 2, 3*sizeof(char));
	
	printf("mio: %s | loro: %s", s, t);
}*/
