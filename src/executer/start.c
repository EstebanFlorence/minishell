/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:28:33 by gcavanna          #+#    #+#             */
/*   Updated: 2023/07/14 18:52:12 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exec_path(t_shell *shell, char *cmd, char **env)
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
		tmp = ft_strjoin(path[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(paths, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_freepaths(paths);
	exit(127);
	return (NULL);
}

void	exec_freepaths(char **paths)
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


int	exec_check(t_shell *shell, t_pars **parser, char **env)
{
	int	i;

	i = 0;
	if (access((*parser)->token[i], X_OK) == 0)
	{
		printf ("SUCCESS :D\n");
		return (0);
	}
	
}

void	ft_exec(t_shell *shell, t_pars **parser, char **env)
{
	//char	*path;

	if (exec_check(shell, parser, env))
		printf("Error: exec_check\n");
	
	
}
