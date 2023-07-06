/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:45:02 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/06 02:42:59 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_exit(t_shell *shell)
{
	free(shell->input);
	free(shell->prompt);
	
	exit (0);
}

int	ft_isvalid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 34 && str[i] == 127)
			return (1);
		i++;
	}
	return (0);
}
