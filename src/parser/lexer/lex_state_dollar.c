/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:13:24 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/19 20:57:47 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_dollar_append(char c, t_lex *lex)
{
	if (numstr(lex->buffer, '$') > 1)
	{
		lex->buffer[lex->len] = '\0';
		lex_multiexpand(lex, lex->shell);
		lex->buffer[lex->len] = c;
		lex->len++;
	}
	else
	{
		lex->buffer[lex->len] = '\0';
		lex_expand(lex, lex->shell);
		lex->buffer[lex->len] = c;
		lex->len++;
	}
	lex->state = STATE_NORMAL;
}

void	state_dollar_exp(char c, t_lex *lex)
{
	if (numstr(lex->buffer, '$') > 2)
	{
		lex->buffer[lex->len] = '\0';
		lex_multiexpand(lex, lex->shell);
	}
	else
	{
		lex->buffer[lex->len] = '\0';
		lex_expand(lex, lex->shell);
	}
	if (c == SINGLE_QUOTE)
		lex->state = STATE_SINGLE_QUOTE;
	else
		lex->state = STATE_DOUBLE_QUOTE;
}

void	state_dollar_end(t_lex *lex, t_tok **token, int *id)
{
	if (numstr(lex->buffer, '$') > 1)
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

void	state_dollar(char c, t_lex *lex, t_tok **token, int *id)
{
	if (c == ' ')
	{
		if (lex->len > 0)
			state_dollar_end(lex, token, id);
	}
	else if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
	{
		if (lex->len > 0)
			state_dollar_exp(c, lex);
	}
	else if (c == '\\')
	{
		if (lex->len > 0)
			state_dollar_append(c, lex);
	}
	else
		lex_append(c, lex);
}
