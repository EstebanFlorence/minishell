/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:24:22 by adi-nata          #+#    #+#             */
/*   Updated: 2023/03/04 16:43:14 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printfu(unsigned int nbr, t_format *flag)
{
	size_t					len;
	char					*snbr;

	len = ft_unsize(nbr);
	snbr = ft_calloc(len + 1, sizeof(char));
	ft_unsconvert(nbr, len - 1, snbr);
	if (!flag->wdt && !flag->meno && !flag->zero
		&& !flag->prc && !flag->spc && !flag->piu)
	{
		ft_putu(snbr, len, flag);
		free(snbr);
		return ;
	}
	ft_managewdtprc(nbr, len, flag);
	if (flag->meno)
		ft_putu(snbr, len, flag);
	ft_checkwdtu(flag);
	if (!flag->meno)
		ft_putu(snbr, len, flag);
	free (snbr);
}

void	ft_putu(char *s, int len, t_format *flag)
{
	int	i;

	i = 0;
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
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
		flag->len += 1;
	}
}

void	ft_checkwdtu(t_format *flag)
{
	if (flag->wdt)
	{
		if (flag->zero)
			ft_putwdt0(flag);
		else
			ft_putwdt(flag);
	}
}
