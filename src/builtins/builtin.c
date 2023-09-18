/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:56:33 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/18 04:15:21 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (2);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (2);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (2);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_pars *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->cmds[0], "echo", 5) == 0)
		return (ft_echo(cmd->cmds));
	if (ft_strncmp(cmd->cmds[0], "cd", 3) == 0)
		return (ft_cd(cmd->cmds, shell));
	if (ft_strncmp(cmd->cmds[0], "pwd", 4) == 0)
		return (ft_pwd(0));
	if (ft_strncmp(cmd->cmds[0], "export", 7) == 0)
		return (ft_export(cmd->cmds, shell));
	if (ft_strncmp(cmd->cmds[0], "unset", 6) == 0)
		return (ft_unset(cmd->cmds, shell));
	if (ft_strncmp(cmd->cmds[0], "env", 4) == 0)
		return (ft_env(shell));
	if (ft_strncmp(cmd->cmds[0], "exit", 5) == 0)
		return (ft_exit(cmd->cmds, shell, cmd));
	return (1);
}
