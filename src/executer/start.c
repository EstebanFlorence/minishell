/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:28:33 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/08 12:40:53 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exec_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 5) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	env_freepaths(paths);
	exit(127);
	return (NULL);
}

void	env_freepaths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free (paths);
}

int	exec_check(t_shell *shell, t_pars **command, char **env)
{
	int	i;

	i = 0;
	if (access((*command)->token[i], X_OK) == 0)
	{
		printf ("SUCCESS :D\n");
		return (0);
	}
}

void	ft_exec(t_shell *shell, t_pars **command, char **env)
{
	//char	*path;
	if (exec_check(shell, parser, env))
		printf("Error: exec_check\n");
}
