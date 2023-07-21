/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_normal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 03:33:21 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/21 00:27:52 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_normal_squote(t_lex *lex, t_tok **token)
{
		// Start of single quoted sequence

	if (lex->len > 0)
	{
		lex->buffer[lex->len] = '\0';
		lex_lstadd(token, lex);
		lex->len = 0;
	}

	lex->state = STATE_SINGLE_QUOTE;

}

void	state_normal_dquote(t_lex *lex, t_tok **token)
{
	// Start of double quoted sequence

	if (lex->len > 0)
	{
		lex->buffer[lex->len] = '\0';
		lex_lstadd(token, lex);
		lex->len = 0;
	}

	lex->state = STATE_DOUBLE_QUOTE;

}

void	state_normal_space(t_lex *lex, t_tok **token)
{

	// End of word

	if (lex->len > 0)
	{
		lex->buffer[lex->len] = '\0';
		lex_lstadd(token, lex);
		lex->len = 0;
	}


}

void	state_normal(char c, t_lex *lex, t_tok **token)
{
	if (c == ' ')
	{
		state_normal_space(lex, token);
	}
	else if (c == DOUBLE_QUOTE)
	{
		state_normal_dquote(lex, token);
	}
	else if (c == SINGLE_QUOTE)
	{
		state_normal_squote(lex, token);
	}
	else if (c == '$')
	{
		// lex_expander()? sia dentro che fuori quotes
			// End eventual word and start expansion

			if (lex->len > 0)
			{
				lex->buffer[lex->len] = '\0';
				lex_lstadd(token, lex);
				lex->len = 0;
				lex->state = STATE_DOLLAR_SIGN;
			}
			else
				lex->state = STATE_DOLLAR_SIGN;
	}
	else
	{
		// Append char to current word

		lex->buffer[lex->len] = c;
		lex->len++;
	}		
}
