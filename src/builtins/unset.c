/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:04:25 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/07 16:10:20 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_shell *shell, char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str && str[i])
	{
		j = 0;
		while (str[i][j] && str[i][j] != '=')
			j++;
		if (str[i][j] != '=')
			ft_unsetenv(&shell, str[i]);
		else
			ft_putchar_fd("not a valid identidier\n", STDERR_FILENO);
		i++;
	}
	return (0);
}
