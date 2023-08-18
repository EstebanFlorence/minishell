/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:21:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/08/18 13:13:15 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Iterate through the parser's commands 

void	execute(t_pars **command, t_shell *shell)
{
	int		i;
	int		j;
	char	*cmd_path;
	t_pars	*tmp;

	i = 0;
	j = 0;
	tmp = (*command);
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

void	shell_executor(t_pars **command, t_shell *shell)
{
	int		status;
	t_pars	*cmd;

	cmd = *command;
	while (cmd)
	{
		//	Pipe
		if (pipe(shell->pipe) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		//	Process
		shell->pid = fork();
		if (shell->pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		//	Child
		if (shell->pid == 0)
		{

			if ((cmd)->prev)
			{
				dup2((cmd)->prev->out, STDIN_FILENO);
				close((cmd)->prev->out);
			}

			if ((cmd)->next)
			{
				dup2(shell->pipe[1], STDOUT_FILENO);
				close(shell->pipe[0]);
				close(shell->pipe[1]);
			}
			printf("command in: %d	out: %d\n", (cmd)->in, (cmd)->out);

			//	Handle redirection
			if ((cmd)->in != STDIN_FILENO)
			{
				dup2((cmd)->in, STDIN_FILENO);
				close((cmd)->in);
				printf("in duppato");
			}
			if ((cmd)->out != STDOUT_FILENO)
			{
				dup2((cmd)->out, STDOUT_FILENO);
				close((cmd)->out);
				printf("out duppato");
			}

			execute(command, shell);

		}
		//	Father
		else
		{
			if ((cmd)->prev)
				close((cmd)->prev->out);
			if ((cmd)->next)
			{
				close(shell->pipe[1]);
				dup2(shell->pipe[0], STDIN_FILENO);
				close(shell->pipe[0]);
			}
		}	

		waitpid(shell->pid, &status, 0);

		(cmd) = (cmd)->next;
	}



/* 	shell->pid = fork();
	if (shell->pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (!shell->pid)
	{
		execute(command, shell);

	}
	else
	{
		waitpid(shell->pid, &status, 0);
	} 
	*/

	
}

