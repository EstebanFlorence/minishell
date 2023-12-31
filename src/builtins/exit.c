/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:03:08 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/10 19:40:08 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **str, t_shell *shell, t_pars *cmd)
{
	int	i;
	int	nexit;

	i = 0;
	while (str && str[i])
		i++;
	if (i == 1)
	{
		pars_free(cmd);
		shell_free(shell);
		exit(0);
	}
	else if (i == 2)
	{
		nexit = ft_atoi(str[1]);
		pars_free(cmd);
		shell_free(shell);
		exit(nexit);
	}
	else
		write(STDERR_FILENO, "exit to many arguments\n", 24);
	return (0);
}
