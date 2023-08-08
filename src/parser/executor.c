/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:21:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/08/08 23:32:50 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Iterate through the parser's commands 

void	execute(t_pars **parser, t_shell *shell)
{
	int		i;
	int		j;
	char	*cmd_path;
	t_pars	*tmp;

	i = 0;
	j = 0;
	tmp = (*parser);
	while (tmp->cmd[i])
	{
		while (shell->paths[j])
		{
			cmd_path = ft_strjoin(shell->paths[j], tmp->cmd[i]);
			if (access(cmd_path, X_OK) == 0)
			{
				execve(cmd_path, tmp->cmd, shell->env);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			free(cmd_path);
			j++;
		}
		j = 0;
		i++;
	}
}

void	shell_executor(t_pars **parser, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (!pid)
	{
		execute(parser, shell);

	}
	else
	{
		waitpid(pid, &status, 0);
	}

	
}

