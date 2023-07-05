/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_di.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 14:39:33 by adi-nata          #+#    #+#             */
/*   Updated: 2023/03/04 16:42:58 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printfdi(int nbr, t_format *flag)
{
	long int	n;
	int			len;
	char		*snbr;

	n = nbr;
	if (nbr == INT_MIN)
		snbr = "2147483648";
	else
	{
		if (n < 0)
			n = n * -1;
		snbr = ft_itoa(n);
	}
	len = (int)ft_strlen(snbr);
	ft_printfdi2(nbr, len, snbr, flag);
}

void	ft_printfdi2(int nbr, int len, char *snbr, t_format *flag)
{
	if (!flag->wdt && !flag->meno && !flag->zero
		&& !flag->prc && !flag->spc && !flag->piu)
	{
		ft_putdi(nbr, snbr, len, flag);
		if (nbr != INT_MIN)
			free(snbr);
		return ;
	}
	ft_managewdtprc(nbr, len, flag);
	if (flag->meno)
		ft_putdi(nbr, snbr, len, flag);
	ft_checkwdtdi(nbr, flag);
	if (!flag->meno)
		ft_putdi(nbr, snbr, len, flag);
	if (nbr != INT_MIN)
		free(snbr);
}

void	ft_putdi(int n, char *s, int len, t_format *flag)
{
	if (!(flag->wdt && flag->zero))
	{
		ft_checkspc(n, flag);
		ft_checkpiu(n, flag);
		ft_checkneg(n, flag);
	}
	if (flag->prc)
	{
		if (!flag->prcquant)
			return ;
		if (flag->prcquant >= len)
		{
			flag->prcquant -= len;
			ft_putprc0(flag);
		}
	}
	ft_putstr(s);
	flag->len += (int)ft_strlen(s);
}

void	ft_checkwdtdi(int n, t_format *flag)
{
	if (flag->wdt)
	{
		if (flag->zero)
		{
			ft_checkspc(n, flag);
			ft_checkpiu(n, flag);
			ft_checkneg(n, flag);
		}
		if (flag->spc || flag->piu || n < 0)
			flag->wdtquant -= 1;
		if (flag->zero)
			ft_putwdt0(flag);
		else
			ft_putwdt(flag);
	}
}
