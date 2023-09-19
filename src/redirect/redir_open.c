/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:04:22 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/19 19:10:27 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_heredoc(t_pars *cmd, int i)
{
	if (cmd->in != -2)
		close(cmd->in);
	//cmd->in = here_doc();
	if (cmd->in < 0)
	{
		perror(cmd->redir_name[i]);
		g_exit = 1;
	}
}

void	redir_input(t_pars *cmd, int i)
{
	if (cmd->in != -2)
		close(cmd->in);
	cmd->in = open(cmd->redir_name[i], O_RDONLY);
	if (cmd->in < 0)
	{
		perror(cmd->redir_name[i]);
		g_exit = 1;
	}
}

void	redir_append(t_pars *cmd, int i)
{
	if (cmd->out != -2)
		close(cmd->out);
	cmd->out = open(cmd->redir_name[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (cmd->out < 0)
	{
		perror(cmd->redir_name[i]);
		g_exit = 1;
	}
}

void	redir_output(t_pars *cmd, int i)
{
	if (cmd->out != -2)
		close(cmd->out);
	cmd->out = open(cmd->redir_name[i], 
			O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (cmd->out < 0)
	{
		perror(cmd->redir_name[i]);
		g_exit = 1;
	}
}
