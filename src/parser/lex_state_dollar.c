/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:13:24 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/11 18:56:43 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_dollarquote_end(t_lex *lex, t_tok **token, int *id)
{
	// End of double quoted sequence and variable name, append expanded value to current word
	if (lex->len > 0)
	{
		if (numstr(lex->buffer, '$') > 2)
		{
			lex->buffer[lex->len] = '\0';
			lex_multiexpand(lex);
			tok_lstadd(token, lex, id);
			lex->len = 0;
		}
		else
		{
			lex->buffer[lex->len] = '\0';
			lex_expand(lex);
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
	// End of variable name, append expanded value to current word
	if (lex->len > 0)
	{
		//	Sequence of multiple expandable variables without spaces
		if (numstr(lex->buffer, '$') > 1)
		{
			lex->buffer[lex->len] = '\0';
			lex_multiexpand(lex);
			lex->buffer[lex->len] = c;
			lex->len++;
		}
		else
		{
			lex->buffer[lex->len] = '\0';
			lex_expand(lex);
			lex->buffer[lex->len] = c;
			lex->len++;
		}
		lex->state = STATE_DOUBLE_QUOTE;
	}
	// Only append metachar to quoted sequence
	else
	{
		lex->buffer[lex->len] = c;
		lex->len++;
		lex->state = STATE_DOUBLE_QUOTE;
	}
}

//	Metacharacters in the same if statement
//	Tokenize (tok_lstadd) buffer only at the end of quoted sequence
void	state_dollarquotes(char c, t_lex *lex, t_tok **token, int *id)
{
	// Expand variable and keep appending
	if (c == ' ' || c == '\\' || c == SINGLE_QUOTE)
	{
		state_dollarquote_append(c, lex);
	}
	else if (c == DOUBLE_QUOTE)
	{
		state_dollarquote_end(lex, token, id);
	}
	else
	{
		lex->buffer[lex->len] = c;
		lex->len++;
	}
}

void	state_dollar(char c, t_lex *lex, t_tok **token, int *id)
{
	if (c == ' ')
	{
		// End of variable name, append expanded value to current word
		if (lex->len > 0)
		{
			//	Sequence of multiple expandable variables without spaces
			if (numstr(lex->buffer, '$') > 1)
			{
				lex->buffer[lex->len] = '\0';
				lex_multiexpand(lex);
				tok_lstadd(token, lex, id);
				lex->len = 0;
			}
			else
			{
				lex->buffer[lex->len] = '\0';
				lex_expand(lex);
				tok_lstadd(token, lex, id);
				lex->len = 0;				
			}
			lex->state = STATE_NORMAL;
		}
	}
	else if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
	{
		//	Expand variable and keep appending -> no lstadd
		//	$USER'$USER' -> esteban$USER
		if (lex->len > 0)
		{
			if (numstr(lex->buffer, '$') > 2)
			{
				lex->buffer[lex->len] = '\0';
				lex_multiexpand(lex);
				//tok_lstadd(token, lex, id);
				//lex->len = 0;
			}
			else
			{
				lex->buffer[lex->len] = '\0';
				lex_expand(lex);
				//tok_lstadd(token, lex, id);
				//lex->len = 0;
			}
			if (c == SINGLE_QUOTE)
				lex->state = STATE_SINGLE_QUOTE;
			else
				lex->state = STATE_DOUBLE_QUOTE;
		}
	}
	else if (c == '\\')
	{
		//	Metachar -> expand variable and append char to expanded variable
		if (lex->len > 0)
		{
			if (numstr(lex->buffer, '$') > 1)
			{
				lex->buffer[lex->len] = '\0';
				lex_multiexpand(lex);
				lex->buffer[lex->len] = c;
				lex->len++;
			}
			else
			{
				lex->buffer[lex->len] = '\0';
				lex_expand(lex);
				lex->buffer[lex->len] = c;
				lex->len++;
			}
			lex->state = STATE_NORMAL;
		}
	}
	else
	{
		lex->buffer[lex->len] = c;
		lex->len++;
	}
}
