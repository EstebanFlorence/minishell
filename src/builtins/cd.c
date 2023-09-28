/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:09:44 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/28 18:34:29 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setenv(char *name, char *value, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0)
		{
			free(shell->env[i]);
			tmp = ft_strjoin(name, "=");
			shell->env[i] = ft_strjoin(tmp, value);
			free(tmp);
			return (0);
		}
		i++;
	}
	while (shell->env[i])
		i++;
	shell->env = ft_realloc(shell->env, sizeof(char *) * (i + 2));
	tmp = ft_strjoin(name, "=");
	shell->env[i] = ft_strjoin(tmp, value);
	shell->env[i + 1] = NULL;
	free(tmp);
	return (0);
}

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
