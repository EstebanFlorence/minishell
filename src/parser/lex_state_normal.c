/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_normal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 03:33:21 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/19 17:23:02 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_normal_squote(t_lex *lex)
{
	if (!lex->in_quotes)
	{
		// Start of single quoted sequence

		lex->state = STATE_SINGLE_QUOTE;
		lex->in_quotes = true;
	}
}

void	state_normal_dquote(t_lex *lex)
{
 	if (!lex->in_quotes)
	{
		// Start of double quoted sequence

		lex->state = STATE_DOUBLE_QUOTE;
		lex->in_quotes = true;
	}
}

void	state_normal_space(char c, t_lex *lex, t_tok **token)
{
	if (!lex->in_quotes)
	{
		// End of word

		if (lex->len > 0)
		{
			lex->word[lex->len] = '\0';
			//if (lex->len < ft_strlen(lex->word))
			lex->start = lex->len;
			//lex->token = ft_substr(lex->word, lex->start, lex->len);
			lex_lstadd(token, lex);
			lex->len = 0;
		}
	}
	else
	{
		// Append space in quoted sequence

		lex->word[lex->len] = c;
		lex->len++;
	}
}
