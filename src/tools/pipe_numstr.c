/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_numstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:36:11 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/28 18:37:09 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_numstr_quote(const char *s, size_t *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] == '\0')
		return (1);
	return (0);
}

void	pipe_numstr_add(size_t *n, size_t *len)
{
	if (*len > 0)
		(*n)++;
	*len = 0;
}

int	pipe_numstr(const char *s, char pipe)
{
	size_t	i;
	size_t	n;
	size_t	len;

	i = 0;
	n = 0;
	len = 0;
	while (1)
	{
		if (s[i] == pipe || s[i] == '\0')
			pipe_numstr_add(&n, &len);
		if (s[i] == pipe && n == 0)
			return (-1);
		else if (s[i] == DOUBLE_QUOTE || s[i] == SINGLE_QUOTE)
			pipe_numstr_quote(s, &i);
		else
			len++;
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (n);
}
