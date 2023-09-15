/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:43:38 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/15 14:53:39 by gcavanna         ###   ########.fr       */
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
			ft_setexport(str[i], NULL, shell);
			i++;
		}
	}
	return (0);
}
