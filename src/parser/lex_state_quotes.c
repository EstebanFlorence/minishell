/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:10:30 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/18 19:20:27 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	state_quotes_single(char c, t_lex *lex)
{

}

void	state_quotes_double(char c, t_lex *lex)
{

} */

void	state_quotes(char c, t_lex *lex)
{
	if (lex->state == STATE_DOUBLE_QUOTE)
	{
		if (c == DOUBLE_QUOTE)
		{
			// End of double quoted sequence

			lex->in_quotes = false;
			lex->state = STATE_NORMAL;
		}
		else if (c == '$')
		{
			// Start expansion

			lex->state = STATE_DOLLAR_SIGN_DOUBLE_QUOTE;
		}
		else
		{
			// Append char to current word inside double quotes

			lex->word[lex->len] = c;
			lex->len++;
		}
	}
	else if (lex->state == STATE_SINGLE_QUOTE)
	{
		if (c == SINGLE_QUOTE)
		{
			// End of single quoted sequence

			lex->in_quotes = false;
			lex->state = STATE_NORMAL;
		}
		else
		{
			// Append char to current word inside single quotes

			lex->word[lex->len] = c;
			lex->len++;
		}	
	}
}
