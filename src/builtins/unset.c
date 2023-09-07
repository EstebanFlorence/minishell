/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:04:25 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/07 17:07:46 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **str, t_shell *shell)
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
			ft_unsetenv(str[i], shell);
		else
			write(STDERR_FILENO, "not a valid identifier\n", 24);
		i++;
	}
	return (0);
}
