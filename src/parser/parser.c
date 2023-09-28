/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:45:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/28 20:45:33 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commander_loop(t_tok *token, t_pars *command)
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
				pars_redir(token, r, command);
				r++;
				token = token->next;
			}
		}
		else
		{
			command->cmds[n] = ft_strdup(token->token);
			n++;
		}
		token = token->next;
	}
	if (n == 0)
		command->exec = false;
}

void	pars_commander(t_tok *token, t_pars *command)
{
	t_tok	*tmp;

	tmp = token;
	commander_alloc(tmp, command);
	tmp = token;
	commander_loop(tmp, command);
}

void	pars_loop(char **inputs, t_tok *token, t_pars **command, t_shell *shell)
{
	int			i;
	static int	n;

	n = 0;
	i = 0;
	while (inputs[i])
	{
		lex_tokenizer(shell, inputs[i], &token, &n);
		if (token == NULL)
		{
			//g_exit = 127;	//	0
			//shell->exit = g_exit;
			shell->exit = 1;
			if (i > 0)
				write(STDERR_FILENO,
					"syntax error near unexpected token: \"|\"\n", 41);
			i++;
			continue ;
		}
		pars_lstadd_back(command, pars_lstnew(i + 1));
		pars_commander(token, pars_lstlast(*command));
		tok_free(token);
		token = NULL;
		i++;
	}
}

void	shell_parser(t_shell *shell, t_pars **command)
{
	t_tok		*token;
	char		**inputs;

	*command = NULL;
	token = NULL;
	inputs = input_split(shell);
	if (inputs == NULL)
		return ;
	pars_loop(inputs, token, command, shell);
	tok_free(token);
	lex_free_inputs(inputs);
}
