/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:45:02 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/24 19:09:41 by gcavanna         ###   ########.fr       */
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
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], tmp, ft_strlen(tmp)))
		{
			content = ft_strdup(shell->env[i] + ft_strlen(tmp));
			free(tmp);
			return (content);
		}
		i++;
	}
	free(tmp);
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
