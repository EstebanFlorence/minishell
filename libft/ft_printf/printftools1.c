/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   printf_tools1.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: adi-nata <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/12/03 20:31:29 by adi-nata		  #+#	#+#			 */
/*   Updated: 2022/12/30 15:25:45 by adi-nata		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putwdt(t_format *flag)
{
	int	i;

	i = flag->wdtquant;
	while (i > 0)
	{
		write(1, " ", 1);
		i -= 1;
		flag->len += 1;
	}
}

void	ft_putwdt0(t_format *flag)
{
	while (flag->wdtquant > 0)
	{
		write(1, "0", 1);
		flag->wdtquant -= 1;
		flag->len += 1;
	}
}

void	ft_putprc0(t_format *flag)
{
	int	quant;

	quant = flag->prcquant;
	while (quant > 0)
	{
		write(1, "0", 1);
		quant -= 1;
		flag->len += 1;
	}
}

void	ft_managewdt(int len, t_format *flag)
{
	if (flag->wdt)
	{
		flag->wdtquant -= len;
		while (flag->wdtquant > 0)
		{
			write(1, " ", 1);
			flag->len += 1;
			flag->wdtquant -= 1;
		}
	}
}

void	ft_managewdtprc(int n, int len, t_format *flag)
{
	if (flag->prc && flag->wdt)
	{
		if (flag->prcquant > flag->wdtquant)
			flag->wdt = 0;
	}
	if (flag->prc)
	{
		if (n && flag->prcquant <= len)
			flag->prc = 0;
	}
	if (flag->wdt)
	{
		if (n && flag->wdtquant <= len)
			flag->wdt = 0;
		if (flag->wdt && flag->prc)
			flag->wdtquant -= flag->prcquant;
		else
			flag->wdtquant -= len;
	}
}
