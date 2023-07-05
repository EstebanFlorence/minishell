/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 23:09:04 by adi-nata          #+#    #+#             */
/*   Updated: 2023/03/04 16:43:45 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_syntax(const char *str, int i, t_format *flag)
{
	int		j;
	int		perc;
	int		spec;
	char	*specset;

	specset = "cspdiuxX%";
	j = 0;
	perc = i + 1;
	spec = i + 1;
	while (str[spec])
	{
		while (specset[j])
		{
			if (str[spec] == specset[j])
			{
				ft_checkflags(str, perc, spec, flag);
				ft_checkformat(str, perc, spec, flag);
				return (spec);
			}
			j++;
		}
		spec++;
		j = 0;
	}
	return (spec);
}

void	ft_checkformat(const char *str, int p, int i, t_format *flag)
{
	size_t		len;
	size_t		x;
	const char	*formstr;

	len = (size_t)i - (size_t)p + 1;
	formstr = ft_substr(str, p, len);
	x = ft_strlen(formstr) - 1;
	ft_wrongflags(formstr, x, flag);
	if (formstr)
		ft_printfer(formstr, x, flag);
	free ((char *)formstr);
}

void	ft_printfer(const char *formstr, int x, t_format *flag)
{
	if (formstr[x] == 'c')
		ft_printfc(va_arg(flag->arg, int), flag);
	else if (formstr[x] == 's')
		ft_printfs(va_arg(flag->arg, char *), flag);
	else if (formstr[x] == 'p')
		ft_printfp(va_arg(flag->arg, long unsigned int), flag);
	else if (formstr[x] == 'd' || formstr[x] == 'i')
		ft_printfdi(va_arg(flag->arg, int), flag);
	else if (formstr[x] == 'u')
		ft_printfu(va_arg(flag->arg, int), flag);
	else if (formstr[x] == 'x' || formstr[x] == 'X')
		ft_printfx(va_arg(flag->arg, unsigned int), flag, formstr, x);
	else if (formstr[x] == '%')
	{
		write(1, "%", 1);
		flag->len += 1;
	}
}
