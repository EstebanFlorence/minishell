/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:45:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/08/03 02:37:09 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_redirect(t_tok *token, t_pars **parser)
{
	if (ft_strncmp(token->token, ">", 2) == 0)
	{
		
	}
	else if (ft_strncmp(token->token, ">>", 3) == 0)
	{

	}	
	else if (ft_strncmp(token->token, "<", 2) == 0)
	{
	
	}
	else if (ft_strncmp(token->token, "<<", 3) == 0)
	{
	
	}
}

void	pars_commander(t_tok *token, t_pars **parser, int id)
{
	int		i;
	int		n;
	char	**cmds;
	t_tok	*tmp;

	pars_lstadd(parser, id);
	tmp = token;
	while (tmp->next && tmp->type != REDIRECT)
		tmp = tmp->next;
	n = tmp->id;
	cmds = (char **)ft_calloc(n + 1, sizeof(char *));
	i = 0;
	tmp = token;
	while (tmp->next)
	{
		if (tmp->type == REDIRECT)
		{

			pars_redirect(token, parser);
		}
		cmds[i] = ft_strdup(tmp->token);
		i++;
		tmp = tmp->next;
	}
	

}

void	shell_parser(t_shell *shell, t_pars **parser)
{
	t_tok		*token;
	static int	n;
	int			i;
	char		**inputs;

	*parser = NULL;
	token = NULL;
	if (pipe_numstr(shell->input, '|') > 1)
		inputs = pipe_split(shell->input, '|');
	else
	{
		inputs = (char **)ft_calloc(2, sizeof(char *));
		inputs[0] = ft_strdup(shell->input);
		inputs[1] = NULL;
	}
	n = 0;
	i = 0;
	while (inputs[i])
	{
		lex_tokenizer(shell, inputs[i], &token, &n);
		pars_commander(token, parser, i + 1);
		tok_free(token);
		i++;
	}

	lex_free_inputs(inputs);
}

void	shell_command(t_shell *shell, t_pars **parser)
{
	shell_parser(shell, parser);

	int i = 0;
	t_pars *tmpp = *parser;
	while (tmpp)
	{
		while (tmpp && tmpp->cmd[i])
			printf("parser id: %d	command: %s\n", tmpp->id, tmpp->cmd[i++]);
		i = 0;
		tmpp = tmpp->next;
	}

	tok_free(token);
	pars_free(*parser);
}

void	pars_free(t_pars *parser)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	while (parser)
	{
		tmp = parser;
		parser = parser->next;
		while (tmp->cmd[i])
			free(tmp->cmd[i++]);
		i = 0;
		free(tmp->cmd);
		free(tmp);
	}
}

/* void	pars_commander(t_tok *token, t_pars **parser, int id)
{
	int		i;
	int		n;
	char	**cmds;
	t_tok	*tmp;

	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	n = tmp->id;
	cmds = (char **)ft_calloc(n + 1, sizeof(char *));
	i = 0;
	tmp = token;
	while (tmp)
	{
		cmds[i] = ft_strdup(tmp->token);
		i++;
		tmp = tmp->next;
	}
	pars_lstadd(parser, cmds, id);

	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);

} */
/*	Test:

	t_tok *tmp = *token;
	while (tmp)
	{
		printf("token id: %d type: %d token: %s\n", tmp->id, tmp->type, tmp->token);
		tmp = tmp->next;
	}

 */