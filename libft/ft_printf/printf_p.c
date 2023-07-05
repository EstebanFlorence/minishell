/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 14:41:31 by adi-nata          #+#    #+#             */
/*   Updated: 2023/03/04 16:41:57 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printfp(unsigned long int nbr, t_format *flag)
{
	int		len;
	char	*base;

	len = 0;
	base = "0123456789abcdef";
	if ((!nbr && !flag->wdt) || (!nbr && flag->wdtquant <= 5))
	{
		write(1, "(nil)", 5);
		flag->len += 5;
		return ;
	}
	if (!nbr)
		len = 5;
	else
		len = hexlen(nbr) + 2;
	if (flag->meno)
		ft_putp(nbr, len, base, flag);
	ft_managewdt(len, flag);
	if (!flag->meno)
		ft_putp(nbr, len, base, flag);
}

void	ft_putp(unsigned long int n, int len, char *base, t_format *flag)
{
	if (!n)
	{
		write(1, "(nil)", 5);
		flag->len += 5;
		return ;
	}
	else
	{
		write(1, "0x", 2);
		flag->len += 2;
		hexconvert(n, len, base, flag);
	}
}
