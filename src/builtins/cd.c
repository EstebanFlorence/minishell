/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:09:44 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/07 17:04:29 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **str, t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;

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
	ft_setenv("OLDPWD", oldpwd, shell);
	ft_setenv("PWD", pwd, shell);
	free(pwd);
	free(oldpwd);
	return (0);
}
