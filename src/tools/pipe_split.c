/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:16:49 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/17 18:32:28 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_splitter_quotes(const char *s, size_t *i, size_t *len)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	(*len)++;
	while (s[*i] && s[*i] != quote)
	{
		(*i)++;
		(*len)++;
	}
	(*len)++;
}

char	*pipe_splitter_add(const char *s, size_t *i, size_t *len)
{
	char	*tok;

	if (*len > 0)
		tok = ft_substr(s, (unsigned int)(*i - *len), *len);
	else
		tok = NULL;
	*len = 0;
	return (tok);
}

void	pipe_splitter(const char *s, char pipe, char **split, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while (j < n)
	{
		if (s[i] == pipe || s[i] == '\0')
		{
			split[j] = pipe_splitter_add(s, &i, &len);
			j++;
		}
		else if (s[i] == DOUBLE_QUOTE || s[i] == SINGLE_QUOTE)
			pipe_splitter_quotes(s, &i, &len);
		else
			len++;
		i++;
	}
}

char	**pipe_split(const char *s, char pipe)
{
	char	**split;
	int		n;

	n = pipe_numstr(s, pipe);
	split = malloc(sizeof(*split) * ((size_t)n + 1));
	pipe_splitter(s, pipe, split, n);
	split[n] = NULL;
	return (split);
}
