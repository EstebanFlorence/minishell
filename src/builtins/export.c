/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:43:38 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/25 19:35:10 by gcavanna         ###   ########.fr       */
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
			ft_printf("declare -x %s\n", shell->env[j]);
			j++;
		}
	}
	else
	{
		if (strchr_index(str[1], '=') == -1)
			return (0);
		while (str[i])
		{
			ft_setexport(str[i], NULL, shell);
			i++;
		}
	}
	return (0);
}
