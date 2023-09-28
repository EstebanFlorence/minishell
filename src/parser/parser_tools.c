/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:43:55 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/28 20:45:12 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commander_alloc(t_tok *token, t_pars *command)
{
	int		n;
	int		r;

	n = 0;
	r = 0;
	while (token)
	{
		if (token->type == REDIRECT)
		{
			if (token->next)
			{
				r++;
				token = token->next;
			}
		}
		else
			n++;
		token = token->next;
	}
	command->cmds = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!r)
		return ;
	command->numred = r;
	command->redirs = (int *)ft_calloc(r, sizeof(int));
	command->redir_name = (char **)ft_calloc(r + 1, sizeof(char *));
}

char	**input_split(t_shell *shell)
{
	int		pipes;
	char	**inputs;

	pipes = pipe_numstr(shell->input, '|');
	if (pipes == -1)
	{
		write(STDERR_FILENO, "syntax error near unexpected token: \"|\"\n", 41);
		g_exit = 1;
		shell->exit = g_exit;
		return (NULL);
	}
	if (pipes > 1)
		inputs = pipe_split(shell->input, '|');
	else
	{
		inputs = (char **)ft_calloc(2, sizeof(char *));
		inputs[0] = ft_strdup(shell->input);
		inputs[1] = NULL;
	}
	return (inputs);
}

void	pars_free_content(t_pars **command)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	tmp = *command;
	*command = (*command)->next;
	while (tmp->cmds[i])
		free(tmp->cmds[i++]);
	free(tmp->cmds);
	i = 0;
	if (tmp->redirs)
	{
		free(tmp->redirs);
		while (tmp->redir_name[i])
			free(tmp->redir_name[i++]);
		free(tmp->redir_name);
		i = 0;
	}
	free(tmp);
}

void	pars_free(t_pars *command)
{
	if (!command)
		return ;
	while (command->prev)
		command = command->prev;
	while (command)
		pars_free_content(&command);
}
