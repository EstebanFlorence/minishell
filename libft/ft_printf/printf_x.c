/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:48:02 by adi-nata          #+#    #+#             */
/*   Updated: 2023/03/04 16:43:19 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printfx(unsigned int nbr, t_format *flag,
		const char *fomrstr, int spec)
{
	int		len;
	char	*base;

	len = hexlen(nbr);
	if (fomrstr[spec] == 'x')
		base = "0123456789abcdef";
	else if (fomrstr[spec] == 'X')
	{
		base = "0123456789ABCDEF";
		flag->x += 1;
	}
	ft_managewdtprc(nbr, len, flag);
	if (flag->meno)
		ft_putx(nbr, base, len, flag);
	ft_checkwdtx(nbr, flag);
	if (!flag->meno)
		ft_putx(nbr, base, len, flag);
}

void	ft_putx(unsigned int n, char *base, int len, t_format *flag)
{
	if (!(flag->wdt && flag->zero))
		ft_checkhash(n, flag);
	if (flag->prc)
	{
		if (n == 0 && !flag->prcquant)
			return ;
		else if (flag->prcquant > len)
		{
			flag->prcquant -= len;
			ft_putprc0(flag);
		}
	}
	hexconvert(n, len, base, flag);
}

void	ft_checkwdtx(unsigned int n, t_format *flag)
{
	if (flag->wdt)
	{
		if (flag->zero || flag->meno)
			ft_checkhash(n, flag);
		if (flag->hash)
			flag->wdtquant -= 2;
		if (flag->zero)
			ft_putwdt0(flag);
		else
			ft_putwdt(flag);
	}
}
