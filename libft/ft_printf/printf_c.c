/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:05:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/03/04 16:42:52 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printfc(char c, t_format *flag)
{
	if (flag->meno)
	{
		write(1, &c, 1);
		flag->len += 1;
	}
	ft_managewdt(1, flag);
	if (!flag->meno)
	{
		write(1, &c, 1);
		flag->len += 1;
	}
}
