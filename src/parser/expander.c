/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 23:11:15 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/24 23:22:21 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	When found $ in token, if expandables, modify token of the node

void	lex_multiexpand(t_lex *lexer)
{
	int		i;
	char	**expandables;
	char	*names;
	char	*var;
	char	*tmp_expanded;
	char	*expanded;

	i = 0;
	names = ft_substr(lexer->buffer, lexer->start, lexer->len);
	expandables = ft_split(names, '$');
	expanded = ft_strdup("");
	while (expandables[i])
	{
		var = getenv(expandables[i]);
		if (var != NULL)
		{
			tmp_expanded = expanded;
			expanded = ft_strjoin(tmp_expanded, var);
			free(tmp_expanded);
		}
		i++;
	}
	lex_bzero(lexer->buffer, lexer->start, (lexer->len - lexer->start));
	lexer->len = lexer->start;
	i = 0;
	while (expanded[i])
	{
		lexer->buffer[lexer->len] = expanded[i];
		lexer->len++;
		i++;
	}
	i = 0;
	while (expandables[i])
		free(expandables[i++]);
	free(expandables);
	free(expanded);
	free(names);
}

void	lex_expand(t_lex *lexer)
{
	char	*name;
	char	*var;
	int		i;

	name = ft_substr(lexer->buffer, lexer->start, lexer->len);
	lex_bzero(lexer->buffer, lexer->start - 1, (lexer->len - lexer->start));
	lexer->len = lexer->start;
	var = getenv(name);
	if (var == NULL)
		return ;
	i = 0;
	while (var[i])
	{
		lexer->buffer[lexer->len] = var[i];
		lexer->len++;
		i++;
	}
	free(name);
}

int	is_expandables(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == SINGLE_QUOTE)
		{
			i++;
			while (s[i] && s[i] != SINGLE_QUOTE)
				i++;
		}
		if (s[i] == '$' && (s[i + 1] != ' ' && s[i + 1] != '\0'))
		{
			j = 1;
		}
		if (j && (s[i] == ' ' || s[i + 1] == '\0'))
		{
			return (1);
		}
		i++;
	}
	return (-1);
}

