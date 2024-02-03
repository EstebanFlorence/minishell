/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:45:02 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/28 18:41:58 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_path(char *path, t_shell *shell)
{
	int		i;
	char	**paths;

	i = 0;
	paths = ft_split(path + 5, ':');
	while (paths[i])
		i++;
	shell->paths = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (paths[++i])
		shell->paths[i] = ft_strjoin(paths[i], "/");
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

void	command_notfound(t_pars *cmd)
{
	write(STDERR_FILENO, "Command not found: ", 20);
	if (cmd->cmds[0])
		write(STDERR_FILENO, cmd->cmds[0], ft_strlen(cmd->cmds[0]));
	else
		write(STDERR_FILENO, "\'\'", 3);
	write(STDERR_FILENO, "\n", 2);
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
		if (s[i] < 32 || s[i] == 127)
			return (1);
		i++;
	}
	return (0);
}
