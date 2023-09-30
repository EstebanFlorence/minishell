/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:22:06 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/29 20:10:12 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_tokenizer_end(t_lex *lex, t_tok **token, int *id)
{
	if (lex->type == -2)
	{
		//g_exit = 2;
		lex->shell->exit = 1;
	}
	else if (lex->len)
	{
		lex->buffer[lex->len] = '\0';
		if (lex->state == STATE_DOLLAR_SIGN)
		{
			if (numstr(lex->buffer, '$') > 1)
				lex_multiexpand(lex, lex->shell);
			else
				lex_expand(lex, lex->shell);
		}
		lex->buffer[lex->len] = '\0';
		tok_lstadd(token, lex, id);
	}
	free(lex);
}

void	lex_tokenizer(t_shell *shell, char *input, t_tok **token, int *id)
{
	t_lex	*lex;
	int		i;

	lex = (t_lex *)ft_calloc(1, sizeof(t_lex));
	lex->state = STATE_NORMAL;
	lex->type = -1;
	lex->len = 0;
	lex->shell = shell;
	i = 0;
	while (input[i] && lex->type != -2)
	{
		if (lex->state == STATE_NORMAL)
			state_normal(input[i], lex, token, id);
		else if (lex->state == STATE_DOUBLE_QUOTE
			|| lex->state == STATE_SINGLE_QUOTE)
			state_quotes(input[i], lex);
		else if (lex->state == STATE_DOLLAR_SIGN)
			state_dollar(input[i], lex, token, id);
		else if (lex->state == STATE_DOLLAR_SIGN_DOUBLE_QUOTE)
			state_dollarquotes(input[i], lex, token, id);
		else if (lex->state == STATE_REDIRECT)
			state_redirect(input[i], lex, token, id);
		i++;
	}
	lex_tokenizer_end(lex, token, id);
}

void	lex_free_inputs(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		free(inputs[i]);
		inputs[i] = NULL;
		i++;
	}
	free(inputs);
}

void	tok_free(t_tok *token)
{
	t_tok	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->token);
		free(tmp);
	}
}
