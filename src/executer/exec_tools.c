/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:47:41 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/26 22:19:22 by adi-nata         ###   ########.fr       */
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
	while (tmp->cmds[i] && shell->paths)
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
	command_notfound(command);
	pars_free(command);
	shell_free(shell);
	exit(127);
}

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
	shell->exit = g_exit;
	pars_free(cmd);
	shell_exit(shell);
}

void	exec_builtin_main(t_pars *cmd, t_shell *shell)
{
	if (cmd->numred)
	{
		exec_redir(cmd, shell);
		handle_redir(cmd);
	}
	g_exit = exec_builtin(cmd, shell);
	shell->exit = g_exit;
	if (cmd->out != -2)
	{
		close(cmd->out);
	}
	if (cmd->in != -2)
	{
		close(cmd->in);
	}
}
