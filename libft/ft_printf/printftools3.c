/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printftools3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:24:00 by adi-nata          #+#    #+#             */
/*   Updated: 2023/03/04 16:43:38 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_unsconvert(unsigned int n, int len, char *snbr)
{
	char	c;

	if (n / 10)
		ft_unsconvert(n / 10, len - 1, snbr);
	c = '0' + n % 10;
	snbr[len] = c;
}

size_t	ft_unsize(long num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		len ++;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

int	hexlen(long unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	else
	{
		while (n != 0)
		{
			n = n / 16;
			i ++;
		}
		return (i);
	}
}

void	hexconvert(long unsigned int n, int len, char *base, t_format *flag)
{
	int	hex;

	if (n == 0 && flag->hex1 == 0)
	{
		write(1, "0", 1);
		flag->len += 1;
		return ;
	}
	if (n != 0)
	{
		hex = n % 16;
		n = n / 16;
		flag->hex1 += 1;
		hexconvert(n, len - 1, base, flag);
		write(1, &base[hex], 1);
		flag->len += 1;
	}
}

void	ft_checkhash(unsigned int n, t_format *flag)
{
	if (n == 0)
		return ;
	else if (flag->hash)
	{
		if (!flag->x)
		{
			write(1, "0x", 2);
			flag->len += 2;
		}
		else if (flag->x)
		{
			write(1, "0X", 2);
			flag->len += 2;
		}
	}
}
