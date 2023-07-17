/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:16:49 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/17 18:32:28 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	shell_numstr(const char *s, char c)
{
	size_t	i;
	size_t	n;
	size_t	len;

	i = 0;
	n = 0;
	len = 0;
	while (1)
	{
		if (s[i] == c || s[i] == '\0')
		{
			if (len != 0)
				n++;
			len = 0;
		}
		else if (s[i] == DOUBLE_QUOTE)
		{
			i++;
			while (s[i] && s[i] != DOUBLE_QUOTE)
				i++;
		}
		else
			len++;
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (n);
}

void	shell_splitta(const char *s, char c, char **split, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*tok;

	i = 0;
	j = 0;
	len = 0;
	while (j < n)
	{
		if (s[i] == c || s[i] == '\0')
		{
			if (len != 0)
			{
				tok = ft_substr(s, (unsigned int)(i - len), len);
				split[j] = tok;
				j++;
			}
			len = 0;
		}
		else if (s[i] == DOUBLE_QUOTE)
		{
			i++;
			while (s[i] && s[i] != DOUBLE_QUOTE)
				i++;
		}
		else
			len++;
		i++;
	}
}

char	**shell_split(const char *s, char c)
{
	char	**split;
	size_t	n;

	n = numstr(s, c);
	split = malloc(sizeof(*split) * (n + 1));
	shell_splitta(s, c, split, n);
	split[n] = NULL;
	return (split);
}

