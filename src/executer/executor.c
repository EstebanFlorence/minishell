/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:21:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/02 19:49:51 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_print(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	execute(t_pars *command, t_shell *shell)
{
	int		i;
	int		j;
	char	*cmd_path;
	t_pars	*tmp;

	i = 0;
	j = 0;
	tmp = command;
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

/* 
	Each cmd needs a stdin (input) and returns an output (to stdout)
   
	 stdin				                                  stdout         
       |                        PIPE                        ↑
       |           |---------------------------|            |
       ↓             |                       |              |
      cmd1   -->    end[1]       ↔       end[0]   -->     cmd2           
                     |                       |
            cmd1   |---------------------------|  end[0]
           output                             reads end[1]
         is written                          and sends cmd1
          to end[1]                          output to cmd2
       (end[1] becomes                      (end[0] becomes 
        cmd1 stdout)                           cmd2 stdin)
 */

void	shell_executor(t_pars **command, t_shell *shell)
{
	int		status;
	t_pars	*cmd;

	cmd = *command;
	while (cmd)
	{
		if (cmd->in == -1 || cmd->out == -1)
		{
			//cmd = cmd->next;
			//continue ;
			break ;
		}
		//	Pipe
		if (cmd->next)
		{
			if (pipe(shell->pipe) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}			
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
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);

			if (cmd->next)
			{
				close(shell->pipe[0]);
				dup2(shell->pipe[1], STDOUT_FILENO);
				close(shell->pipe[1]);
			}
			else
			{
				//	Handle redirection
				printf("in %i out %i\n", cmd->in, cmd->out);
				if (cmd->in != -2)
				{
					dup2(cmd->in, STDIN_FILENO);
					//close(cmd->in);
				}
				if (cmd->out != -2)
				{
					dup2(cmd->out, STDOUT_FILENO);
					//close(cmd->out);
				}				
			}

			execute(cmd, shell);

		}
		//	Father
		else
		{
			signal(SIGINT, signal_print);
			signal(SIGQUIT, signal_print);

			if (cmd->next)
			{
				close(shell->pipe[1]);
				dup2(shell->pipe[0], STDIN_FILENO);
				close(shell->pipe[0]);
			}
			close(cmd->in);
			close(cmd->out);
			waitpid(shell->pid, &status, 0);

		}
		cmd = cmd->next;
	}
	dup2(shell->in, STDIN_FILENO);
	dup2(shell->out, STDOUT_FILENO);

}

