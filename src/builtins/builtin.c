/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:56:33 by gcavanna          #+#    #+#             */
/*   Updated: 2023/09/06 11:10:00 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_control_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	ft_builtin(t_shell *shell)
{
	if (ft_strncmp(shell->cmd, "echo", 5) == 0)
		return (ft_echo(shell));
	if (ft_strncmp(shell->cmd, "cd", 3) == 0)
		return (ft_cd(shell));
	if (ft_strncmp(shell->cmd, "pwd", 4) == 0)
		return (ft_pwd(shell));
	if (ft_strncmp(shell->cmd, "export", 7) == 0)
		return (ft_export(shell));
	if (ft_strncmp(shell->cmd, "unset", 6) == 0)
		return (ft_unset(shell));
	if (ft_strncmp(shell->cmd, "env", 4) == 0)
		return (ft_env(shell));
	if (ft_strncmp(shell->cmd, "exit", 5) == 0)
		return (ft_exit(shell));
	return (0);
}
