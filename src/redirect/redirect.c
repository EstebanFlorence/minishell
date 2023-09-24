/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:06 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/24 20:02:40 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_pars *cmd, int i)
{
	char	*tmplimiter;
	char	*line;
	int		heredoc;

	tmplimiter = ft_strjoin(cmd->redir_name[i], "\n");
	line = get_next_line(STDIN_FILENO);
	heredoc = open(HEREPATH, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (heredoc < 0)
		perror("heredoc");
	while (line)
	{
		if (!ft_strncmp(line, tmplimiter, ft_strlen(tmplimiter) + 1))
		{
			close(heredoc);
			free(tmplimiter);
			free(line);
			get_next_line(-42);
			heredoc = open(HEREPATH, O_RDONLY, 0666);
			return (heredoc);
		}
		ft_putstr_fd(line, heredoc);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	return (-1);
}

void	exec_redir(t_pars *cmd)
{
	int	i;
	int	n;

	i = 0;
	n = cmd->numred;
	while (i < n)
	{
		if (cmd->redirs[i] == OUTPUT)
			redir_output(cmd, i);
		else if (cmd->redirs[i] == APPEND)
			redir_append(cmd, i);
		else if (cmd->redirs[i] == INPUT)
			redir_input(cmd, i);
		else if (cmd->redirs[i] == HEREDOC)
			redir_heredoc(cmd, i);
		i++;
	}
}

void	pars_redir(t_tok *token, int r, t_pars *command)
{
	if (ft_strncmp(token->token, ">", 2) == 0)
	{
		command->redirs[r] = OUTPUT;
		command->redir_name[r] = ft_strdup(token->next->token);
	}
	else if (ft_strncmp(token->token, ">>", 3) == 0)
	{
		command->redirs[r] = APPEND;
		command->redir_name[r] = ft_strdup(token->next->token);
	}
	else if (ft_strncmp(token->token, "<", 2) == 0)
	{
		command->redirs[r] = INPUT;
		command->redir_name[r] = ft_strdup(token->next->token);
	}
	else if (ft_strncmp(token->token, "<<", 3) == 0)
	{
		command->redirs[r] = HEREDOC;
		command->redir_name[r] = ft_strdup(token->next->token);
	}
}
