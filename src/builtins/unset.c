/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:04:25 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/28 18:33:16 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unsetexp(char *name, t_shell *shell)
{
	int		i;
	int		j;
	char	**exp;

	i = 0;
	j = 0;
	exp = shell->export;
	while (exp && exp[i])
	{
		if (ft_strncmp(exp[i], name, ft_strlen(name)) == 0)
		{
			free(exp[i]);
			while (exp[i + j])
			{
				exp[i + j] = exp[i + j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_unsetenv(char *name, t_shell *shell)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	j = 0;
	env = shell->env;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			free(env[i]);
			while (env[i + j])
			{
				env[i + j] = env[i + j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **str, t_shell *shell)
{
	int	i;
	int	j;

	if (str[1] && ft_strncmp(str[1], "PATH", 5) == 0 && shell->paths)
		shell_freepath(shell);
	i = 1;
	while (str && str[i])
	{
		j = 0;
		while (str[i][j] && str[i][j] != '=')
			j++;
		if (str[i][j] != '=')
		{
			ft_unsetenv(str[i], shell);
			ft_unsetexp(str[i], shell);
		}
		else
			write(STDERR_FILENO, "not a valid identifier\n", 24);
		i++;
	}
	return (0);
}
