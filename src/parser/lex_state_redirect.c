/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:28:07 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/03 19:10:10 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_redirect(char c, t_lex *lex, t_tok **token, int *id)
{
	if ((c == '<' && !ft_strchr(">|$", lex->buffer[lex->len - 1]) && lex->len == 1) ||
		(c == '>' && !ft_strchr("<|$", lex->buffer[lex->len - 1]) && lex->len == 1))
	{
		lex->buffer[lex->len] = c;
		lex->len++;
		return ;
	}
	if (ft_strchr("<>|$", c))
	{
		//	Syntax error
		perror("syntax error near unexpected token");
	}
	//	End of redirect symbol
	if (lex->len > 0)
	{
		lex->type = REDIRECT;
		lex->buffer[lex->len] = '\0';
		tok_lstadd(token, lex, id);
		lex->len = 0;
	}
	if (c != ' ')
	{
		lex->buffer[lex->len] = c;
		lex->len++;			
	}
	lex->state = STATE_NORMAL;
}
