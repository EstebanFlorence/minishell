/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:21:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/19 17:48:54 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_end(t_shell *shell)
{
	int	status;

	waitpid(shell->pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit = WEXITSTATUS(status);
		shell->exit = g_exit;
	}
	else if (WIFSIGNALED(status))
	{
		g_exit = WTERMSIG(status) + 128;
		shell->exit = g_exit;
	}
}

void	parent_process(t_pars *cmd, t_shell *shell)
{
	signal(SIGINT, signal_print);
	signal(SIGQUIT, signal_print);
	if (cmd->exec == false && cmd->next)
		close(shell->pipe[1]);
	else if (cmd->exec == true && cmd->next)
	{
		close(shell->pipe[1]);
		if (cmd->cmds[0])
		{
			dup2(shell->pipe[0], STDIN_FILENO);
			close(shell->pipe[0]);
		}
	}
	close_redir(cmd);
	parent_end(shell);
}

void	child_process(t_pars *cmd, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->numred)
		exec_redir(cmd, shell);
	if (cmd->exec == false)
	{
		close_redir(cmd);
		if (cmd->next)
			close(shell->pipe[0]);
		pars_free(cmd);
		shell_exit(shell);
	}
	else if (cmd->next)
		handle_piperedir(cmd, shell);
	else
		handle_redir(cmd);
	if (is_builtin(cmd->cmds[0]))
		exec_builtin_fork(cmd, shell);
	else if (cmd->exec == true)
		execvshell(cmd, shell);
}

void	fork_command(t_pars *cmd, t_shell *shell)
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
		if (cmd->next)
		{
			if (pipe(shell->pipe) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		if (!cmd->next && is_builtin(cmd->cmds[0]) == 2)
			exec_builtin_main(cmd, shell);
		else if (shell->paths && shell->exit == 0)
			fork_command(cmd, shell);
		cmd = cmd->next;
	}
	dup2(shell->in, STDIN_FILENO);
	dup2(shell->out, STDOUT_FILENO);
}
