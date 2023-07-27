/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_innit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:45:21 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/27 23:25:38 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*tok_lstnew(t_lex *lexer, int *id)
{
	t_tok	*new;

	new = (t_tok *)ft_calloc(1, sizeof(t_tok));
	if (new == NULL)
		return (NULL);
	new->id = ++(*id);
	new->type = lex_type(lexer->buffer, lexer->shell);
	new->token = ft_strdup(lexer->buffer);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_tok	*tok_lstlast(t_tok *token)
{
	t_tok	*next;

	if (token != NULL)
	{
		next = token;
		while (1)
		{
			if (next->next == NULL)
				return (next);
			next = next->next;
		}
	}
	return (NULL);
}

void	tok_lstadd_back(t_tok **token, t_tok *new)
{
	t_tok	*last;

	if (!token)
		return ;
	if (*token == NULL)
		*token = new;
	else
	{
		last = tok_lstlast(*token);
		if (last != NULL)
		{
			last->next = new;
			new->prev = last;
		}
	}
}

void	tok_lstadd(t_tok **token, t_lex *lexer, int *id)
{

	tok_lstadd_back(token, tok_lstnew(lexer, id));
	
}
