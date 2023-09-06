/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:18:53 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/06 11:01:02 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **str)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if (str[1] && ft_strncmp(str[1], "-n", 2) == 0)
	{
		no_newline = 1;
		i++;
	}
	while (str && str[0] && str[i])
	{
		ft_printf("%s", str[i]);
		if (str[i + 1])
			ft_printf(" ");
		i++;
	}
	if (no_newline == 0)
		ft_printf("\n");
	return (0);
}
