/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_innit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:45:21 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/14 01:06:03 by adi-nata         ###   ########.fr       */
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

t_lex	*lex_lstnew(int i, char *s, int type)
{
	t_lex	*new;

	new = (t_lex *)malloc(sizeof(t_lex) * 1);
	if (new == NULL)
		return (NULL);
	new->id = i + 1;
	new->type = type;
	new->token = s;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lex	*lex_lstlast(t_lex *lexer)
{
	t_lex	*next;

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

void	lex_lstadd_back(t_lex **lexer, t_lex *new)
{
	t_lex	*last;

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

void	lex_innit(t_shell *shell, t_lex **lexer)
{
	int	i;

	i = -1;
	while (shell->inputs[++i])
		lex_lstadd_back(lexer, lex_lstnew(i, shell->inputs[i], lex_type(shell->inputs[i])));
}
