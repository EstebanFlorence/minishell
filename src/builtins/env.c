/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:47:30 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/06 11:06:30 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *shell)
{
	char	**env;

	env = shell->env;
	while (envn && *env)
	{
		ft_printf("%s\n", *env);
		env++;
	}
	return (0);
}
