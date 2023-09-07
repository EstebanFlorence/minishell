/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:03:08 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/07 16:10:18 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **str)
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
		ft_putchar_fd("exit to many arguments\n", STDERR_FILENO);
}
