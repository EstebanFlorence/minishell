/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:11:21 by adi-nata          #+#    #+#             */
/*   Updated: 2023/05/10 14:11:38 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atol(const char *nbr)
{
	int			sign;
	long int	res;

	sign = 1;
	res = 0;
	while (*nbr == ' ' || \
			(*nbr >= '\t' && *nbr <= '\r'))
		nbr++;
	if (*nbr == '-' || *nbr == '+')
	{
		if (*nbr == '-')
			sign *= -1;
		nbr++;
	}
	while (*nbr >= '0' && *nbr <= '9')
	{
		res = res * 10 + *nbr - '0';
		nbr++;
	}
	return (res * sign);
}
