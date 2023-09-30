/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:23:26 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/30 18:14:47 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc(char **env, size_t size)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(size);
	while (env && env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = NULL;
	if (env)
	{
		i = 0;
		while (env[i])
			free(env[i++]);
		free(env);
	}
	return (new);
}

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

int	ft_stupid_norm(char *pwd, char *oldpwd)
{
	free(pwd);
	free(oldpwd);
	return (chdir(getenv("HOME")));
}
