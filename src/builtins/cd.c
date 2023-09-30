/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:09:44 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/30 18:52:53 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_home_not_set(char *pwd, char *oldpwd)
{
	write(STDERR_FILENO, "minishell: cd: HOME not set :(\n", 32);
	free(pwd);
	free(oldpwd);
	return (1);
}

static int	ft_norm_too_args(char *pwd, char *oldpw)
{
	free(pwd);
	free(oldpw);
	write(STDERR_FILENO, "minishell: cd: Too many arguments\n", 35);
	return (1);
}

static int	ft_norm_folder_not_found(char *pwd, char *oldpwd)
{
	perror(pwd);
	free(pwd);
	free(oldpwd);
	return (1);
}

char	*ft_getenv(t_shell *shell, const char *var)
{
	int	i;

	i = 0;
	if (var == NULL)
		return (NULL);
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var) - 1) == 0
			&& shell->env[i][ft_strlen(var)] != 0
			&& shell->env[i][ft_strlen(var)] == '=')
			return (&shell->env[i][ft_strlen(var) + 1]);
		i++;
	}
	return (NULL);
}

int	ft_cd(char **str, t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	oldpwd = ft_strdup(pwd);
	if (ft_getenv(shell, "HOME") == NULL && str[1] == NULL)
		return (ft_home_not_set(pwd, oldpwd));
	if (ft_getenv(shell, "HOME") == NULL && str[1] != NULL && str[1][0] != '/'
		&& ft_strcmp(str[1], "-") != 0)
		return (ft_home_not_set(pwd, oldpwd));
	if (str[1] == NULL)
		return (ft_stupid_norm(pwd, oldpwd));
	else if (ft_strcmp(str[1], "-") == 0)
		chdir(getenv("OLDPWD"));
	if (str[2] != NULL)
		return (ft_norm_too_args(pwd, oldpwd));
	else if (chdir(str[1]) == -1 && ft_strcmp(str[1], "-") != 0)
		return (ft_norm_folder_not_found(pwd, oldpwd));
	free(pwd);
	pwd = getcwd(NULL, 0);
	ft_setenv("OLDPWD", oldpwd, shell);
	ft_setenv("PWD", pwd, shell);
	free(pwd);
	free(oldpwd);
	return (0);
}
