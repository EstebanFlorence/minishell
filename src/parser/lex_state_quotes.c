/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:10:30 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/24 23:23:45 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_quotes_single(char c, t_lex *lex, t_tok **token, int *id)
{
		if (c == SINGLE_QUOTE)
		{
			// End of single quoted sequence

/* 			if (lex->len > 0)
			{
				lex->buffer[lex->len] = '\0';
				lex_lstadd(token, lex, id);
				lex->len = 0;
			} */

			lex->state = STATE_NORMAL;
		}
		else
		{
			// Append char to current word inside single quotes

			lex->buffer[lex->len] = c;
			lex->len++;
		}	
}

void	state_quotes_double(char c, t_lex *lex, t_tok **token, int *id)
{
		if (c == DOUBLE_QUOTE)
		{
			// End of double quoted sequence

/* 			if (lex->len > 0)
			{
				lex->buffer[lex->len] = '\0';
				lex_lstadd(token, lex, id);
				lex->len = 0;
			} */

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

void	state_quotes(char c, t_lex *lex, t_tok **token, int *id)
{
	if (lex->state == STATE_DOUBLE_QUOTE)
	{
		state_quotes_double(c, lex, token, id);
	}
	else if (lex->state == STATE_SINGLE_QUOTE)
	{
		state_quotes_single(c, lex, token, id);
	}
}
