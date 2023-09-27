/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:23:26 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/27 18:12:47 by adi-nata         ###   ########.fr       */
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

/* int	ft_setexport_addexp(char *name, char *value, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->export && shell->export[i])
		i++;
	shell->export = ft_realloc(shell->export, sizeof(char *) * (i + 2));
	tmp = ft_strjoin(name, NULL);
	shell->export[i] = ft_strjoin(tmp, value);
	shell->export[i + 1] = NULL;
	free(tmp);
	return (0);
} */
