/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:43:38 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/27 18:11:26 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **str, t_shell *shell)
{
	int	i;

	if (str[1] == NULL)
	{
		i = 0;
		while (shell->env && shell->env[i])
			ft_printf("declare -x %s\n", shell->env[i++]);
	}
	else
	{
		i = 1;
		while (str[i])
		{
			ft_setexport(str[i], NULL, shell);
			if (ft_strncmp(str[i], "PATH", 5) == 0)
				set_path(str[i], shell);
			i++;
		}
	}
	return (0);
}
