/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:43:38 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/07 17:06:15 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **str, t_shell *shell)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (str[1] == NULL)
	{
		while (shell->env[j])
		{
			ft_printf("%s\n", shell->env[j]);
			j++;
		}
	}
	else
	{
		while (str[i])
		{
			ft_setenv(str[i], NULL, shell);
			i++;
		}
	}
	return (0);
}
