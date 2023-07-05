/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 22:27:49 by adi-nata          #+#    #+#             */
/*   Updated: 2023/03/04 16:41:27 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_checkflags(const char *str, int p, int i, t_format *flag)
{
	int		j;
	char	*flagset;

	j = 0;
	flagset = "-0.# +";
	while (p <= i)
	{
		if (str[p] == flagset[j])
			flag->meno += 1;
		else if (str[p] == flagset[++j] && (flag->wdt == 0 && flag->prc == 0))
			flag->zero += 1;
		else if (str[p] == flagset[++j])
			flag->prc += 1;
		else if (str[p] == flagset[++j])
			flag->hash += 1;
		else if (str[p] == flagset[++j])
			flag->spc += 1;
		else if (str[p] == flagset[++j])
			flag->piu += 1;
		else
			ft_checkflags2(str, p, flag);
		p++;
		j = 0;
	}
}

int	ft_checkflags2(const char *str, int p, t_format *flag)
{
	char	*wdtchar;
	char	*prchar;

	if (ft_isdigit(str[p]))
		ft_checkdigitflags(str, p, flag);
	else
		return (0);
	if (flag->wdtlen > 0 && flag->wdtquant == 0)
	{
		flag->wdt = 1;
		wdtchar = ft_substr(str, p, flag->wdtlen);
		flag->wdtquant = ft_atoi(wdtchar);
		free (wdtchar);
	}
	if (flag->prclen > 0 && flag->prcquant == 0)
	{
		prchar = ft_substr(str, p, flag->prclen);
		flag->prcquant = ft_atoi(prchar);
		free (prchar);
	}
	return (1);
}

void	ft_checkdigitflags(const char *str, int i, t_format *flag)
{
	if (flag->prc == 0 && flag->wdtlen == 0)
	{
		while (ft_isdigit(str[i]))
		{
			flag->wdtlen += 1;
			i++;
		}
	}
	if (flag->prc == 1 && flag->prclen == 0)
	{
		while (ft_isdigit(str[i]))
		{
			flag->prclen += 1;
			i++;
		}
	}
}

int	ft_wrongflags(const char *formstr, int x, t_format *flag)
{
	if (flag->piu && flag->spc)
		flag->spc = 0;
	if (flag->prc && flag->zero)
		flag->zero = 0;
	if (formstr[x] == '%' && flag->zero)
		flag->zero = 0;
	return (1);
}
