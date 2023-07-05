/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:05:42 by adi-nata          #+#    #+#             */
/*   Updated: 2022/10/21 00:41:38 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (ss1[i] != ss2[i] || ss1[i] == 0 || ss2[i] == 0)
			return (ss1[i] - ss2[i]);
		i++;
	}
	return (0);
}

/*int main()
{
	char *s1 = "dio";
	char *s2 = "dio";
	
	char *ss1 = "dio";
	char *ss2 = "dio";
	
	printf ("%d\n", ft_strncmp(s1, s2, 10));
	printf ("%d", strncmp(s1, s2, 10));
	
}*/
