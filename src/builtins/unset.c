/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:04:25 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/26 16:37:19 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **str, t_shell *shell)
{
	int	i;
	int	j;

	if (str[1] && ft_strncmp(str[1], "PATH", 5) == 0 && shell->paths)
	{
		i = 0;
		while (shell->paths[i])
			free(shell->paths[i++]);
		free(shell->paths);
		shell->paths = NULL;
	}
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
