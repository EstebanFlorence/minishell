/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 23:11:15 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/22 17:55:17 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	When found $ in token, if expandables, modify token of the node

char	*lex_expander_reass(char **s)
{
	int		i;
	//char	*tmp1;
	//char	*tmp2;
	
	i = 0;
	while (s[i])
	{


		i++;
	}
	return (NULL);
}

/* char	*lex_expander_newtok(char *s)
{

} */

void	lex_expander(t_tok *token)
{
	t_tok	*tmp;
	char	**dollars;
	char	*new_token;
	int		i;

	tmp = token;
	dollars = ft_split(tmp->token, '$');
	i = 0;
	while (dollars[i])
	{
		new_token = NULL; //lex_expander_newtok(dollars[i]);

		if (new_token)
		{
			free(dollars[i]);
			dollars[i] = ft_strdup(new_token);
			free(new_token);
		}
		i++;
	}
	if (i > 1)
	{
		new_token = lex_expander_reass(dollars);
	}
}

void	lex_multiexpand(t_lex *lexer)
{
	int		i;
	char	**expandables;
	char	*var;
	char	*tmp_expanded;
	char	*expanded;

	i = 0;
	expandables = ft_split(lexer->buffer, '$');
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
	ft_strlcpy(lexer->buffer, expanded, ft_strlen(expanded) + 1);
	i = 0;
	while (expandables[i])
		free(expandables[i++]);
	free(expandables);
	free(expanded);
}

void	lex_expand(char *s)
{
	char	*var;

	if (!s)
		return ;
	var = getenv(s);
	if (var != NULL)
	{
		ft_strlcpy(s, var, ft_strlen(var) + 1);
	}

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

