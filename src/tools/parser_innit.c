/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_innit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:16:16 by adi-nata          #+#    #+#             */
/*   Updated: 2023/08/03 02:18:30 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*pars_lstnew(int id)
{
	t_pars	*new;

	new = (t_pars *)malloc(sizeof(t_pars) * 1);
	if (new == NULL)
		return (NULL);

	new->id = id;

	new->in = STDIN_FILENO;
	new->out = STDOUT_FILENO;

	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_pars	*pars_lstlast(t_pars *parser)
{
	t_pars	*next;

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

void	pars_lstadd_back(t_pars **parser, t_pars *new)
{
	t_pars	*last;

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

void	pars_lstadd(t_pars **parser, int id)
{
	pars_lstadd_back(parser, pars_lstnew(id));
}
