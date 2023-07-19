/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_innit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:45:21 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/19 17:01:11 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_type(char *s)
{
	if (ft_strncmp(s, ">", 2) == 0)
	{
		return (TRUNC);
	
	}
	else if (ft_strncmp(s, ">>", 3 == 0))
	{
		return (APPEND);

	}	
	else if (ft_strncmp(s, "<", 2) == 0)
	{
		return (INPUT);
	
	}
	else if (ft_strncmp(s, "<<", 3) == 0)
	{
		return (HEREDOC);
	
	}
	else if (ft_strncmp(s, "|", 2) == 0)
	{
		return (PIPE);
	}
	else if (ft_strncmp(s, "$", 2) == 0)
		return (EXPAND);
	return (CMD);
}

t_tok	*lex_lstnew(int i, t_lex *lexer)
{
	t_tok	*new;

	new = (t_tok *)malloc(sizeof(t_tok) * 1);
	if (new == NULL)
		return (NULL);
	new->id = i + 1;
	new->type = lex_type(lexer->word);
	new->token = ft_strdup(lexer->word);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_tok	*lex_lstlast(t_tok *token)
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

void	lex_lstadd_back(t_tok **token, t_tok *new)
{
	t_tok	*last;

	if (!token)
		return ;
	if (*token == NULL)
		*token = new;
	else
	{
		last = lex_lstlast(*token);
		if (last != NULL)
		{
			last->next = new;
			new->prev = last;
		}
	}
}

void	lex_lstadd(t_tok **token, t_lex *lexer)
{
	static int	i = 0;

	lex_lstadd_back(token, lex_lstnew(i, lexer));
	i++;
}
