/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_state_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:28:07 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/26 18:31:15 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_redirect(char c, t_lex *lex, t_tok **token, int *id)
{
	if ((c == '<' && lex->buffer[lex->len - 1] != '>' && lex->len == 1)
		|| (c == '>' && lex->buffer[lex->len - 1] != '<' && lex->len == 1))
	{
		lex_append(c, lex);
		return ;
	}
	else if (ft_strchr("<>|$", c))
	{
		write(STDERR_FILENO, "syntax error near unexpected token", 35);
		ft_printf(" \"%c\"\n", c);
		lex->type = -2;
		return ;
	}
	if (lex->len > 0)
	{
		lex->type = REDIRECT;
		lex->buffer[lex->len] = '\0';
		tok_lstadd(token, lex, id);
		lex->len = 0;
	}
	if (c != ' ')
		lex_append(c, lex);
	lex->state = STATE_NORMAL;
	lex->type = -1;
}
