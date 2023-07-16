/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_innit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:45:21 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/16 17:43:27 by adi-nata         ###   ########.fr       */
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
	return (EMPTY);
}

t_tok	*lex_lstnew(int i, char *s, int type)
{
	t_tok	*new;

	new = (t_tok *)malloc(sizeof(t_tok) * 1);
	if (new == NULL)
		return (NULL);
	new->id = i + 1;
	new->type = type;
	new->token = s;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_tok	*lex_lstlast(t_tok *lexer)
{
	t_tok	*next;

	if (lexer != NULL)
	{
		next = lexer;
		while (1)
		{
			if (next->next == NULL)
				return (next);
			next = next->next;
		}
	}
	return (NULL);
}

void	lex_lstadd_back(t_tok **lexer, t_tok *new)
{
	t_tok	*last;

	if (!lexer)
		return ;
	if (*lexer == NULL)
		*lexer = new;
	else
	{
		last = lex_lstlast(*lexer);
		if (last != NULL)
		{
			last->next = new;
			new->prev = last;
		}
	}
}

void	lex_add(t_shell *shell, t_tok **lexer, char *token)
{
	static int	i = 0;

	lex_lstadd_back(lexer, lex_lstnew(i, token, lex_type(shell->inputs[i])));
	i++;
}
