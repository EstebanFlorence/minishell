/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:21:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/07 22:38:14 by adi-nata         ###   ########.fr       */
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
	if (access(command->cmds[i], F_OK) == 0)
	{
		execve(command->cmds[i], command->cmds, shell->env);
		perror("execve1");
		exit(126);
	}
	tmp = command;
	while (tmp->cmds[i])
	{
		while (shell->paths[j])
		{
			cmd_path = ft_strjoin(shell->paths[j], tmp->cmds[i]);
			if (access(cmd_path, F_OK) == 0)
			{
				execve(cmd_path, tmp->cmds, shell->env);
				perror("execve2");
				exit(126);
			}
			free(cmd_path);
			j++;
		}
		j = 0;
		i++;
	}
	exit(127);
}

void	parent_process(t_pars *cmd, t_shell *shell)
{
	int	status;

	signal(SIGINT, signal_print);
	signal(SIGQUIT, signal_print);

	if (cmd->next)
	{
		close(shell->pipe[1]);
		dup2(shell->pipe[0], STDIN_FILENO);
		close(shell->pipe[0]);
	}
	if (cmd->in != -2)
		close(cmd->in);
	if (cmd->out != -2)
		close(cmd->out);
	waitpid(shell->pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		shell->exit = exit_status;
	}
}

void	child_process(t_pars *cmd, t_shell *shell)
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
		if (cmd->in != -2)
		{
			dup2(cmd->in, STDIN_FILENO);
			//close(cmd->in);
		}
		//else
		//	dup2(shell->in, STDIN_FILENO);
		if (cmd->out != -2)
		{
			dup2(cmd->out, STDOUT_FILENO);
			//close(cmd->out);
		}
		//else
		//	dup2(shell->out, STDOUT_FILENO);
	}
	if (is_builtin(cmd->cmds[0]))
	{
		exit_status = exec_builtin(cmd, shell);
		shell->exit = exit_status;
		exit(exit_status);
	}
	else if (cmd->exec == true)
		execute(cmd, shell);
}

void	exec_command(t_pars *cmd, t_shell *shell)
{
	shell->pid = fork();
	if (shell->pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (shell->pid == 0)
	{
		child_process(cmd, shell);
	}
	else
	{
		parent_process(cmd, shell);
	}

}

void	shell_executor(t_pars **command, t_shell *shell)
{
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
/* 		if (!cmd->next && is_builtin(cmd->cmds[0]))
		{
			exit_status = exec_builtin(cmd, shell);
			shell->exit = exit_status;
			continue ;
		} */
		if (cmd->next)
		{
			if (pipe(shell->pipe) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		exec_command(cmd, shell);

		cmd = cmd->next;
	}
	dup2(shell->in, STDIN_FILENO);
	dup2(shell->out, STDOUT_FILENO);
}

