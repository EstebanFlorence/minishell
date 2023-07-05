/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:01:09 by adi-nata          #+#    #+#             */
/*   Updated: 2022/12/27 00:54:24 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include<stdio.h>
//#include<stdlib.h>
#include "libft.h"

int	converti(const char *nptr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (((char *)nptr)[i] != '\0')
	{
		if (((char *)nptr)[i] >= '0' && ((char *)nptr)[i] <= '9')
			j = j * 10 + (((char *)nptr)[i] - '0');
		else
			return (j);
		i++;
	}
	return (j);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (((char *)nptr)[i] == ' ' ||
			(((char *)nptr)[i] >= '\t' && ((char *)nptr)[i] <= '\r'))
		i++;
	if (((char *)nptr)[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (((char *)nptr)[i] == '+')
		i++;
	res = converti(&((char *)nptr)[i]);
	return (res * sign);
}

/*int main(void)
{
    //1
    char sa[] = "       \t \r -2147fds8483647fds";
    printf("1-mine: %d\n", ft_atoi(sa));
    char s[] = "       \t \r -2147fds8483647fds";
    printf("1-original: %d\n\n", atoi(s));
    //2
    char sas[] = "       \t \r 2147483647";
    printf("2-mine: %d\n", ft_atoi(sas));
    char ss[] = "       \t \r 2147483647";
    printf("2-orignial: %d\n\n", atoi(ss));
    //3
    char saw[] = "       \t \r 2147483647";
    printf("3-mine: %d\n", ft_atoi(saw));
    char sw[] = "       \t \r 2147483647";
    printf("3-original: %d\n\n", atoi(sw));
    //4
    char saq[] = "+2147483647";
    printf("4-mine: %d\n", ft_atoi(saq));
    char sq[] = "+2147483647";
    printf("4-original: %d\n\n", atoi(sq));
    //5
    char sae[] = "-2147483648";
    printf("5-mine: %d\n", ft_atoi(sae));
    char se[] = "-2147483648";
    printf("5-original: %d\n\n", atoi(se));
    //6
    char sar[] = "-0";
    printf("6-mine: %d\n", ft_atoi(sar));
    char sr[] = "-0";
    printf("6-original: %d\n\n", atoi(sr));
    //7
    char sat[] = "       \t \r g -2147fds8483647fds";
    printf("7-mine: %d\n", ft_atoi(sat));
    char st[] = "  \t   \r    g    -2147fds483647few4f";
    printf("7-original: %d\n\n", atoi(st));
    //8
    char say[] = "       \t \r -+2147fds8483647fds";
    printf("8-mine: %d\n", ft_atoi(say));
    char sy[] = "       \t \r    -+2147fds483647few4f";
    printf("8-original: %d\n\n", atoi(sy));
    //9
    char say9[] = "       \t \r + 2147fds8483647fds";
    printf("9-mine: %d\n", ft_atoi(say9));
    char sy9[] = "       \t \r    + 2147fds483647few4f";
    printf("9-original: %d\n\n", atoi(sy9));
    //10
    char say9a[] = "0";
    printf("10-mine: %d\n", ft_atoi(say9a));
    char sy9a[] = "0";
    printf("10-original: %d\n\n", atoi(sy9a));
    return (0);
}*/
