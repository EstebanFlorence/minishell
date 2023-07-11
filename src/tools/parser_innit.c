/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_innit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:16:16 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/11 20:19:11 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*pars_lstnew(char *s, int id)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser) * 1);
	if (new == NULL)
		return (NULL);
	new->id = id + 1;
	new->token = ft_strdup(s);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_parser	*pars_lstlast(t_parser *parser)
{
	t_parser	*next;

	if (parser != NULL)
	{
		next = parser;
		while (1)
		{
			if (next->next == NULL)
				return (next);
			next = next->next;
		}
	}
	return (NULL);
}

void	pars_lstadd_back(t_parser **parser, t_parser *new)
{
	t_parser	*last;

	if (!parser)
		return ;
	if (*parser == NULL)
		*parser = new;
	else
	{
		last = pars_lstlast(*parser);
		if (last != NULL)
		{
			last->next = new;
			new->prev = last;
		}
	}
}
