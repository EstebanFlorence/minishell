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

int	pipe_numstr(const char *s, char pipe)
{
	size_t	i;
	size_t	n;
	size_t	len;
	char	quote;

	i = 0;
	n = 0;
	len = 0;
	while (1)
	{
		if (s[i] == pipe || s[i] == '\0')
		{
			if (len > 0)
				n++;
			len = 0;
		}
		if (s[i] == pipe && n == 0)
			return (-1);
		else if (s[i] == DOUBLE_QUOTE || s[i] == SINGLE_QUOTE)
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == '\0')
				break ;
		}
		else
			len++;
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (n);
}

void	pipe_splitter(const char *s, char pipe, char **split, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	quote;
	char	*tok;

	i = 0;
	j = 0;
	len = 0;
	while (j < n)
	{
		if (s[i] == pipe || s[i] == '\0')
		{
			if (len > 0)
			{
				tok = ft_substr(s, (unsigned int)(i - len), len);
				split[j] = tok;
				j++;
			}
			len = 0;
		}
		else if (s[i] == DOUBLE_QUOTE || s[i] == SINGLE_QUOTE)
		{
			quote = s[i];
			i++;
			len++;
			while (s[i] && s[i] != quote)
			{
				i++;
				len++;
			}
			len++;
		}
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
