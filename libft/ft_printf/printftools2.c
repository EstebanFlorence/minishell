/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printftools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:50:56 by adi-nata          #+#    #+#             */
/*   Updated: 2023/03/04 16:43:32 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstrprc(char *s, t_format *flag)
{
	int		i;

	i = 0;
	while (flag->prcquant > 0)
	{
		write(1, &s[i], 1);
		i++;
		flag->prcquant -= 1;
		flag->len += 1;
	}
}

void	ft_checkneg(int n, t_format *flag)
{
	if (!flag->spc && !flag->piu)
	{
		if (n < 0)
		{
			write(1, "-", 1);
			flag->len += 1;
		}		
	}
}

void	ft_checkmeno(int n, t_format *flag)
{
	if (!flag->spc && !flag->piu && flag->prc)
	{
		if (n < 0)
		{
			write(1, "-", 1);
			flag->len += 1;
		}		
	}
}

void	ft_checkspc(int n, t_format *flag)
{
	if (flag->spc)
	{
		if (n < 0)
		{
			write(1, "-", 1);
			flag->len += 1;
		}
		else
		{
			write(1, " ", 1);
			flag->len += 1;
		}
	}
}

void	ft_checkpiu(int n, t_format *flag)
{
	if (flag->piu)
	{
		if (n < 0)
		{
			write(1, "-", 1);
			flag->len += 1;
		}
		else
		{
			write(1, "+", 1);
			flag->len += 1;
		}
	}
}
