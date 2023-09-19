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

void	execvshell(t_pars *command, t_shell *shell)
{
	int		i;
	int		j;
	char	*cmd_path;
	t_pars	*tmp;

	i = 0;
	j = 0;
	exec1(command, shell);
	tmp = command;
	while (tmp->cmds[i])
	{
		while (shell->paths[j])
		{
			cmd_path = ft_strjoin(shell->paths[j], tmp->cmds[i]);
			exec2(cmd_path, tmp, command, shell);
			free(cmd_path);
			j++;
		}
		j = 0;
		i++;
	}
	write(STDERR_FILENO, "Command not found: ", 20);
	if (tmp->cmds[0])
		write(STDERR_FILENO, tmp->cmds[0], ft_strlen(tmp->cmds[0]));
	else
		write(STDERR_FILENO, "\'\'", 3);
	write(STDERR_FILENO, "\n", 2);
	pars_free(command);
	shell_free(shell);
	exit(127);
}

void	parent_process(t_pars *cmd, t_shell *shell)
{
	int	status;

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
	waitpid(shell->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit = WTERMSIG(status) + 128;
}

void	child_process(t_pars *cmd, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->numred)
		exec_redir(cmd);
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
		else
			exec_command(cmd, shell);
		cmd = cmd->next;
	}
	dup2(shell->in, STDIN_FILENO);
	dup2(shell->out, STDOUT_FILENO);
}
