/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:43:38 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/28 18:33:30 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setexport_addenv(char *name, char *value, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->env[i])
		i++;
	shell->env = ft_realloc(shell->env, sizeof(char *) * (i + 2));
	tmp = ft_strjoin(name, NULL);
	shell->env[i] = ft_strjoin(tmp, value);
	shell->env[i + 1] = NULL;
	free(tmp);
	return (0);
}

int	ft_setexport(char *name, char *value, t_shell *shell)
{
	int		i;
	char	*var;
	char	*tmp;

	if (strchr_index(name, '=') > 0)
		var = ft_substr(name, 0, (size_t)strchr_index(name, '='));
	else
		var = ft_strdup(name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var)) == 0)
		{
			free(shell->env[i]);
			tmp = ft_strjoin(name, NULL);
			shell->env[i] = ft_strjoin(tmp, value);
			free(var);
			free(tmp);
			return (0);
		}
		i++;
	}
	free(var);
	ft_setexport_addenv(name, value, shell);
	return (0);
}

char	*varalloc(char **str)
{
	int		i;
	char	*var;

	i = 1;
	if (strchr_index(str[i], '=') > 0)
		var = ft_substr(str[i], 0, (size_t)strchr_index(str[i], '='));
	else
		var = ft_strdup(str[i]);
	return (var);
}

int	ft_export(char **str, t_shell *shell)
{
	int		i;
	char	*var;

	if (str[1] == NULL)
	{
		i = 0;
		while (shell->env && shell->env[i])
			ft_printf("declare -x %s\n", shell->env[i++]);
	}
	else
	{
		i = 1;
		var = varalloc(str);
		while (str[i])
		{
			ft_setexport(str[i], NULL, shell);
			if (ft_strncmp(var, "PATH", 5) == 0)
				set_path(str[i], shell);
			i++;
		}
		free(var);
	}
	return (0);
}
