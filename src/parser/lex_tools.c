/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:56:22 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/19 19:35:09 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_append(char c, t_lex *lex)
{
	lex->buffer[lex->len] = c;
	lex->len++;
}

void	lex_bzero(void *s, unsigned int start, int end)
{
	int	i;

	i = start;
	while (i < end)
		((unsigned char *)s)[i++] = '\0';
}

int	is_command(const char *cmd, t_shell *shell)
{
	int		i;
	char	*cmd_path;

	if (access(cmd, F_OK))
		return (1);
	i = 0;
	while (shell->paths[i])
	{
		cmd_path = ft_strjoin(shell->paths[i], cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			free(cmd_path);
			return (1);
		}
		free(cmd_path);
		i++;
	}
	return (0);
}

int	lex_type(const char *s, t_shell *shell)
{
	if (ft_strlen(s) < 1)
		return (EMPTY);
	else if (is_command(s, shell))
		return (CMD);
	return (WORD);
}
