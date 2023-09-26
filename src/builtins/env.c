/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:47:30 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/26 22:19:05 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *shell)
{
	char	**env;

	if (!shell->paths)
	{
		write(STDERR_FILENO, "Command not found: env\n", 24);
		return (127);
	}
	env = shell->env;
	while (env && *env)
	{
		ft_printf("%s\n", *env);
		env++;
	}
	return (0);
}
