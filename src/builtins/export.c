/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:43:38 by gcavanna          #+#    #+#             */
/*   Updated: 2023/08/30 16:03:45 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_export(t_shell *shell, char **str)
{
    int i;
    int j;

    i = 1;
    j = 0;
    if (str[1] == NULL)
    {
        while (shell->env[j]) //Shell->env is a char **, so this is a loop that prints all the strings in the array
        {
            ft_printf("%s\n", shell->env[j]);
            j++;
        }   
    }
    else
    {
        while (str[i])
        {
            ft_setenv(&shell, str[i], NULL);
            i++;
        }
    }
    return (0);
}