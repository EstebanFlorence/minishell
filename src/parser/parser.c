/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:45:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/26 18:18:09 by adi-nata         ###   ########.fr       */
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
	if (r)
	{
		command->numred = r;
		command->redirs = (int *)ft_calloc(r, sizeof(int));
		command->redir_name = (char **)ft_calloc(r + 1, sizeof(char *));
	}
}

void	pars_commander(t_tok *token, t_pars *command)
{
	int		n;
	int		r;
	t_tok	*tmp;

	n = 0;
	r = 0;
	tmp = token;
	commander_alloc(tmp, command);
	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIRECT)
		{
			if (tmp->next)
			{
				pars_redir(tmp, r, command);
				r++;
				tmp = tmp->next;
			}
		}
		else
		{
			command->cmds[n] = ft_strdup(tmp->token);
			n++;
		}
		tmp = tmp->next;
	}
	if (n == 0)
		command->exec = false;
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

void	shell_parser(t_shell *shell, t_pars **command)
{
	t_tok		*token;
	static int	n;
	int			i;
	char		**inputs;

	*command = NULL;
	token = NULL;
	n = 0;
	i = 0;
	inputs = input_split(shell);
	if (inputs == NULL)
		return ;
	while (inputs[i])
	{
		lex_tokenizer(shell, inputs[i], &token, &n);
		if (token == NULL)
		{
			g_exit = 2;
			shell->exit = g_exit;
			if (i > 0)
				write(STDERR_FILENO, "syntax error near unexpected token: \"|\"\n", 41);
			i++;
			continue ;
		}
		pars_lstadd_back(command, pars_lstnew(i + 1));
		pars_commander(token, pars_lstlast(*command));
		tok_free(token);
		token = NULL;
		i++;
	}
	tok_free(token);
	lex_free_inputs(inputs);
}

void	pars_free(t_pars *command)
{
	int		i;
	t_pars	*tmp;

	if (!command)
		return ;
	while (command->prev)
		command = command->prev;
	i = 0;
	while (command)
	{
		tmp = command;
		command = command->next;
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
}
