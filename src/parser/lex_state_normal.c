/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_normal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 03:33:21 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/27 23:24:53 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_normal_dollar(t_lex *lex)
{
	lex->buffer[lex->len] = '$';
	lex->len++;
	lex->start = lex->len;
	lex->state = STATE_DOLLAR_SIGN;
}

void	state_normal_squote(t_lex *lex)
{
	// Start of single quoted sequence
	lex->state = STATE_SINGLE_QUOTE;
}

void	state_normal_dquote(t_lex *lex)
{
	// Start of double quoted sequence
	lex->state = STATE_DOUBLE_QUOTE;
}

void	state_normal_space(t_lex *lex, t_tok **token, int *id)
{
	// End of word
	if (lex->len > 0)
	{
		lex->buffer[lex->len] = '\0';
		tok_lstadd(token, lex, id);
		lex->len = 0;
	}
}

void	state_normal(char c, t_lex *lex, t_tok **token, int *id)
{
	if (c == ' ')
	{
		state_normal_space(lex, token, id);
	}
	else if (c == DOUBLE_QUOTE)
	{
		lex->state = STATE_DOUBLE_QUOTE;
	}
	else if (c == SINGLE_QUOTE)
	{
		lex->state = STATE_SINGLE_QUOTE;
	}
	else if (c == '$')
	{
		state_normal_dollar(lex);
	}
	else
	{
		// Append char to current word
		lex->buffer[lex->len] = c;
		lex->len++;
	}		
}
