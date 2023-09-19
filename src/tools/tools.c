/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:45:02 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/19 22:54:31 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_print(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

char	*shell_getenv(char *var, t_shell *shell)
{
	int		i;
	char	*content;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strnstr(shell->env[i], var, ft_strlen(var)))
		{
			content = ft_strdup(shell->env[i] + ft_strlen(var) + 1);
			return (content);
		}
		i++;
	}
	return (NULL);
}

int	strchr_index(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_isvalid(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) < 1 || ft_strlen(s) > INPUT_SIZE)
		return (0);
	while (s[i])
	{
		if (s[i] < 32 && s[i] == 127)
			return (1);
		i++;
	}
	return (0);
}

void	shell_free(t_shell *shell)
{
	int	i;

	rl_clear_history();
	free(shell->input);
	free(shell->prompt);
	i = 0;
	while (shell->env[i])
		free(shell->env[i++]);
	free(shell->env);
	i = 0;
	while (shell->paths[i])
		free(shell->paths[i++]);
	free(shell->paths);
}

void	shell_exit(t_shell *shell)
{
	int	i;

	rl_clear_history();
	free(shell->input);
	free(shell->prompt);
	i = 0;
	while (shell->env[i])
		free(shell->env[i++]);
	free(shell->env);
	i = 0;
	while (shell->paths[i])
		free(shell->paths[i++]);
	free(shell->paths);
	exit(g_exit);
}
