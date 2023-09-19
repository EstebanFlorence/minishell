/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_dollarquotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:25:06 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/19 19:40:17 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_dollarquote_end(t_lex *lex, t_tok **token, int *id)
{
	if (lex->len > 0)
	{
		if (numstr(lex->buffer, '$') > 2)
		{
			lex->buffer[lex->len] = '\0';
			lex_multiexpand(lex, lex->shell);
			tok_lstadd(token, lex, id);
			lex->len = 0;
		}
		else
		{
			lex->buffer[lex->len] = '\0';
			lex_expand(lex, lex->shell);
			tok_lstadd(token, lex, id);
			lex->len = 0;
		}
		lex->state = STATE_NORMAL;
	}
	else
		lex->state = STATE_NORMAL;
}

void	state_dollarquote_append(char c, t_lex *lex)
{
	if (lex->len > 0)
	{
		if (numstr(lex->buffer, '$') > 1)
		{
			lex->buffer[lex->len] = '\0';
			lex_multiexpand(lex, lex->shell);
			lex_append(c, lex);
		}
		else
		{
			lex->buffer[lex->len] = '\0';
			lex_expand(lex, lex->shell);
			lex_append(c, lex);
		}
		lex->state = STATE_DOUBLE_QUOTE;
	}
	else
	{
		lex_append(c, lex);
		lex->state = STATE_DOUBLE_QUOTE;
	}
}

void	state_dollarquotes(char c, t_lex *lex, t_tok **token, int *id)
{
	if (c == ' ' || c == '\\' || c == SINGLE_QUOTE)
	{
		state_dollarquote_append(c, lex);
	}
	else if (c == DOUBLE_QUOTE)
	{
		state_dollarquote_end(lex, token, id);
	}
	else
		lex_append(c, lex);
}
