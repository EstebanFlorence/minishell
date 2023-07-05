/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:03:05 by adi-nata          #+#    #+#             */
/*   Updated: 2022/12/27 00:54:17 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	len(long num)
{
	size_t	n;

	if (num <= 0)
		n = 1;
	else
		n = 0;
	while (num != 0)
	{
		num /= 10;
		n++;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	size_t	size;
	long	num;
	char	*itoa;

	size = len(n);
	num = n;
	itoa = (char *)malloc(sizeof(char) * (size + 1));
	if (!itoa)
		return (NULL);
	if (num < 0)
	{
		itoa[0] = '-';
		num *= -1;
	}
	itoa[size] = '\0';
	while (1)
	{
		itoa[size -1] = (num % 10) + '0';
		num /= 10;
		size--;
		if (num == 0)
			break ;
	}
	return (itoa);
}
