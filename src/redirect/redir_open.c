/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:04:22 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/02 16:30:37 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_heredoc(int i, t_pars *cmd, t_shell *shell)
{
	if (cmd->in != -2)
		close(cmd->in);
	cmd->in = here_doc(i, cmd, shell);
	if (cmd->in < 0)
	{
		perror(cmd->redir_name[i]);
		g_exit = 1;
		shell->exit = g_exit;
		cmd->exec = false;
	}
}

void	redir_input(int i, t_pars *cmd, t_shell *shell)
{
	if (cmd->in != -2)
		close(cmd->in);
	cmd->in = open(cmd->redir_name[i], O_RDONLY);
	if (cmd->in < 0)
	{
		perror(cmd->redir_name[i]);
		g_exit = 1;
		shell->exit = g_exit;
		cmd->exec = false;
	}
}

void	redir_append(int i, t_pars *cmd, t_shell *shell)
{
	if (cmd->out != -2)
		close(cmd->out);
	cmd->out = open(cmd->redir_name[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (cmd->out < 0)
	{
		perror(cmd->redir_name[i]);
		g_exit = 1;
		shell->exit = g_exit;
		cmd->exec = false;
	}
}

void	redir_output(int i, t_pars *cmd, t_shell *shell)
{
	if (cmd->out != -2)
		close(cmd->out);
	cmd->out = open(cmd->redir_name[i],
			O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (cmd->out < 0)
	{
		perror(cmd->redir_name[i]);
		g_exit = 1;
		shell->exit = g_exit;
		cmd->exec = false;
	}
}
