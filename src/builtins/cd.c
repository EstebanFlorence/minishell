/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:09:44 by gcavanna          #+#    #+#             */
/*   Updated: 2023/08/30 11:31:41 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_cd(char **str)
{
    char    *pwd;
    char    *oldpwd;

    pwd = getcwd(NULL, 0);
    oldpwd = ft_strdup(pwd);
    if (str[1] == NULL)
        chdir(getenv("HOME"));
    else if (ft_strcmp(str[1], "-") == 0)
        chdir(getenv("OLDPWD"));
    else
        chdir(str[1]);
    free(pwd);
    pwd = getcwd(NULL, 0);
    ft_setenv(&shell, "OLDPWD", oldpwd);
    ft_setenv(&shell, "PWD", pwd);
    free(pwd);
    free(oldpwd);
    return (0);
}