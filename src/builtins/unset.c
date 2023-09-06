/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:04:25 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/06 11:07:09 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_shell *shell, char **str)
{
	int	i;

	i = 1;
	while (str && str[i])
	{
		ft_unsetenv(&shell, str[i]);
		i++;
	}
	return (0);
}
