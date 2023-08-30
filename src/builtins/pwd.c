/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:06:55 by gcavanna          #+#    #+#             */
/*   Updated: 2023/08/30 10:09:25 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_pwd(char **str)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    ft_printf("%s\n", pwd);
    free(pwd);
    return (0);
}