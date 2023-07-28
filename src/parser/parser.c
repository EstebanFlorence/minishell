/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:45:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/28 19:37:52 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_commander(t_tok *token, t_pars **parser, int id)
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

}

void	shell_parser(t_shell *shell, t_tok **token, t_pars **parser)
{
	static int	id;
	int			i;
	char		**inputs;

	if (pipe_numstr(shell->input, '|') > 1)
		inputs = pipe_split(shell->input, '|');
	else
	{
		inputs = (char **)ft_calloc(2, sizeof(char *));
		inputs[0] = ft_strdup(shell->input);
		inputs[1] = NULL;
	}
	id = 0;
	i = 0;
	while (inputs[i])
	{
		lex_tokenizer(shell, inputs[i], token, &id);
		pars_commander(*token, parser, i);
		tok_free(*token);
		*token = NULL;
		i++;
	}

	lex_free_inputs(inputs);
	//tok_free(token);
}

void	shell_command(t_shell *shell, t_pars **parser)
{
	t_tok	*token;

	(void)parser;
	token = NULL;

	shell_parser(shell, &token, parser);

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

/*	Test:

	t_tok *tmp = *token;
	while (tmp)
	{
		printf("token id: %d type: %d token: %s\n", tmp->id, tmp->type, tmp->token);
		tmp = tmp->next;
	}

 */