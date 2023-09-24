/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:04:25 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/24 19:25:21 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **str, t_shell *shell)
{
	int	i;
	int	j;

	if (strncmp(str[1], "PATH", 5) == 0)
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
