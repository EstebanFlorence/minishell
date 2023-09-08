/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcavanna <gcavanna@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:28:07 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/08 12:48:40 by gcavanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_redirect(char c, t_lex *lex, t_tok **token, int *id)
{
	if ((c == '<' && lex->buffer[lex->len - 1] != '>' && lex->len == 1)
		|| (c == '>' && lex->buffer[lex->len - 1] != '<' && lex->len == 1))
	{
		lex->buffer[lex->len] = c;
		lex->len++;
		return ;
	}
	else if (ft_strchr("<>|$", c))
	{
		//	Syntax error
		write(STDERR_FILENO, "syntax error near unexpected token", 35);
		ft_printf(" \"%c\"\n", c);
		lex->type = -2;
		return ;
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
