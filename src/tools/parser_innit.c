/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_innit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:16:16 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/07 22:13:52 by adi-nata         ###   ########.fr       */
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

	new->in = -2;
	new->out = -2;

	new->exec = true;

	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_pars	*pars_lstlast(t_pars *command)
{
	t_pars	*next;

	if (command != NULL)
	{
		next = command;
		while (1)
		{
			if (next->next == NULL)
				return (next);
			next = next->next;
		}
	}
	return (NULL);
}

void	pars_lstadd_back(t_pars **command, t_pars *new)
{
	t_pars	*last;

	if (!command)
		return ;
	if (*command == NULL)
		*command = new;
	else
	{
		last = pars_lstlast(*command);
		if (last != NULL)
		{
			last->next = new;
			new->prev = last;
		}
	}
}

void	pars_lstadd(t_pars **command, int id)
{
	pars_lstadd_back(command, pars_lstnew(id));
}
