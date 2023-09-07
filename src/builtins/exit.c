/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:03:08 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/07 17:05:24 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (i == 1)
		exit(0);
	else if (i == 2)
		exit(ft_atoi(str[1]));
	else
		write(STDERR_FILENO, "exit to many arguments\n", 24);
	return (0);
}
