/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:39:18 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/19 18:55:26 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_pars *cmd, t_shell *shell)
{
	if (cmd->next)
	{
		if (cmd->in == -2)
			close(shell->pipe[0]);
		if (cmd->out == -2)
			close(shell->pipe[1]);
	}
}

void	close_redir(t_pars *cmd)
{
	if (cmd->in != -2)
		close(cmd->in);
	if (cmd->out != -2)
		close(cmd->out);
}

void	handle_redir(t_pars *cmd)
{
	if (cmd->in != -2)
	{
		close(STDIN_FILENO);
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != -2)
	{
		close(STDOUT_FILENO);
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
}

void	handle_piperedir(t_pars *cmd, t_shell *shell)
{
	close(shell->pipe[0]);
	if (cmd->in != -2)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != -2)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	else
	{
		dup2(shell->pipe[1], STDOUT_FILENO);
		close(shell->pipe[1]);
	}
}
