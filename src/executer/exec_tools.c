/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:47:41 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/19 17:49:48 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec1(t_pars *command, t_shell *shell)
{
	if (command->cmds[0] == NULL)
		return ;
	if (access(command->cmds[0], F_OK) == 0)
	{
		execve(command->cmds[0], command->cmds, shell->env);
		perror("execve1");
		pars_free(command);
		shell_free(shell);
		exit(126);
	}
}

void	exec2(char *cmd_path, t_pars *tmp, t_pars *command, t_shell *shell)
{
	if (command->cmds[0] == NULL)
		return ;
	if (access(cmd_path, F_OK) == 0)
	{
		execve(cmd_path, tmp->cmds, shell->env);
		perror("execve2");
		pars_free(command);
		shell_free(shell);
		exit(126);
	}
}

void	exec_builtin_fork(t_pars *cmd, t_shell *shell)
{
	g_exit = exec_builtin(cmd, shell);
	pars_free(cmd);
	shell_exit(shell);
}

void	exec_builtin_main(t_pars *cmd, t_shell *shell)
{
	if (cmd->numred)
	{
		exec_redir(cmd);
		handle_redir(cmd);
	}
	exec_builtin(cmd, shell);
	if (cmd->out != -2)
	{
		close(cmd->out);
	}
	if (cmd->in != -2)
	{
		close(cmd->in);
	}
}
