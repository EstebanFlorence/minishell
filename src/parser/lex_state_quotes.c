/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:10:30 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/26 15:32:27 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_quotes_single(char c, t_lex *lex)
{
		if (c == SINGLE_QUOTE)
		{
			// End of single quoted sequence
			lex->state = STATE_NORMAL;
		}
		else
		{
			// Append char to current word inside single quotes
			lex->buffer[lex->len] = c;
			lex->len++;
		}	
}

void	state_quotes_double(char c, t_lex *lex)
{
		if (c == DOUBLE_QUOTE)
		{
			// End of double quoted sequence
			lex->state = STATE_NORMAL;
		}
		else if (c == '$')
		{
			// Start expansion inside double quotes
			lex->buffer[lex->len] = '$';
			lex->len++;
			lex->start = lex->len;
			lex->state = STATE_DOLLAR_SIGN_DOUBLE_QUOTE;
		}
		else
		{
			// Append char to current word inside double quotes
			lex->buffer[lex->len] = c;
			lex->len++;
		}
}

void	state_quotes(char c, t_lex *lex)
{
	if (lex->state == STATE_DOUBLE_QUOTE)
	{
		state_quotes_double(c, lex);
	}
	else if (lex->state == STATE_SINGLE_QUOTE)
	{
		state_quotes_single(c, lex);
	}
}
