/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_innit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:16:16 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/28 01:13:58 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*pars_lstnew(char **s, int id)
{
	int		n;
	t_pars	*new;

	if (!s)
		return (NULL);
	n = 0;
	while (s[n])
		n++;
	new = (t_pars *)malloc(sizeof(t_pars) * 1);
	if (new == NULL)
		return (NULL);
	new->id = id;

	new->cmd = (char **)ft_calloc(n + 1, sizeof(char *));
	n = 0;
	while (s[n])
	{
		new->cmd[n] = ft_strdup(s[n]);
		n++;
	}


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

void	pars_lstadd(t_pars **parser, char **s, int id)
{
	pars_lstadd_back(parser, pars_lstnew(s, id));
}
