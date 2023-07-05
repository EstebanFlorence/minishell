/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:29:59 by adi-nata          #+#    #+#             */
/*   Updated: 2023/03/04 16:39:05 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int			i;
	int			ret;
	t_format	*flag;

	flag = (t_format *)malloc(sizeof(t_format));
	flag = ft_flag_init(flag);
	va_start(flag->arg, str);
	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '%' && ft_strlen(str) > 1)
		{
			i = ft_syntax(str, i, flag);
			ret += flag->len;
			flag = ft_flag_init(flag);
		}
		else
			ret += write(1, &str[i], 1);
		i++;
	}
	va_end(flag->arg);
	free(flag);
	return (ret);
}

t_format	*ft_flag_init(t_format *flag)
{
	flag->meno = 0;
	flag->zero = 0;
	flag->hash = 0;
	flag->spc = 0;
	flag->piu = 0;
	flag->len = 0;
	flag->wdt = 0;
	flag->prc = 0;
	flag->wdtlen = 0;
	flag->prclen = 0;
	flag->wdtquant = 0;
	flag->prcquant = 0;
	flag->hex1 = 0;
	flag->x = 0;
	return (flag);
}
