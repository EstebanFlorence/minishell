/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:18:53 by gcavanna          #+#    #+#             */
/*   Updated: 2023/08/28 17:34:30 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_echo(char **str)
{
    int i;
    int flag;

    i = 1;
    flag = 0;

    if (str[1] && ft_strncmp(str[1], "-n", 2) == 0)
    {
        flag = 1;
        i++;
    }
    while (str && str[0] && str[i])
    {
        ft_printf("%s", str[i]);
        if (str[i + 1])
            ft_printf(" ");
        i++;
    }
    if (flag == 0)
        ft_printf("\n");
    return (0);
}