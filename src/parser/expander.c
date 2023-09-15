/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 23:11:15 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/15 15:24:10 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	When found $ in token, if expandables, modify token of the node

char	*lex_expand_status(char *s)
{
	int		i;
	int		j;
	char	*exp;
	char	*status;

	i = 0;
	j = is_status(s);
	status = ft_itoa(g_exit);
	if (ft_strlen(s) > 1)
	{
		if (j == 0)
		{
			exp = ft_calloc((ft_strlen(s) + ft_strlen(status) + 1),
					sizeof(char));
			while (status[i])
			{
				exp[i] = status[i];
				i++;
			}
			i++;
		}
		else
			exp = ft_calloc((ft_strlen(s) - j + 1), sizeof(char));
		while (s[j])
		{
			exp[i] = s[j];
			i++;
			j++;
		}
		free(status);
		return (exp);
	}
	return (status);
}

int	is_status(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '?')
			return (i);
		i++;
	}
	return (-1);
}

char	*shell_getenv(char *var, t_shell *shell)
{
	int		i;
	char	*content;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strnstr(shell->env[i], var, ft_strlen(var)))
		{
			content = ft_strdup(shell->env[i] + ft_strlen(var) + 1);
			return (content);
		}
		i++;
	}
	return (NULL);
}

void	lex_multiexpand(t_lex *lexer, t_shell *shell)
{
	int		i;
	char	**expandables;
	char	*names;
	char	*var;
	char	*tmp_expanded;
	char	*expanded;
	char	*status;

	i = 0;
	names = ft_substr(lexer->buffer, lexer->start, lexer->len);
	expandables = ft_split(names, '$');
	expanded = ft_strdup("");
	while (expandables[i])
	{
		var = shell_getenv(expandables[i], shell);
		if (is_status(expandables[i]) >= 0)
		{
			status = lex_expand_status(expandables[i]);
			tmp_expanded = expanded;
			expanded = ft_strjoin(tmp_expanded, status);
			free(status);
			free(tmp_expanded);
		}
		else if (var != NULL)
		{
			tmp_expanded = expanded;
			expanded = ft_strjoin(tmp_expanded, var);
			free(tmp_expanded);
		}
		free(var);
		i++;
	}
	lex_bzero(lexer->buffer, lexer->start - 1, (lexer->len - lexer->start));
	lexer->len = lexer->start - 1;
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

void	lex_expand(t_lex *lexer, t_shell *shell)
{
	int		i;
	char	*name;
	char	*var;

	if (lexer->len == 1)
		return ;
	name = ft_substr(lexer->buffer, lexer->start, (lexer->len - lexer->start));
	lex_bzero(lexer->buffer, lexer->start - 1, lexer->len);
	lexer->len = lexer->start - 1;
	i = 0;
	if (is_status(name) >= 0)
	{
		var = lex_expand_status(name);
		free(name);
		while (var[i])
		{
			lexer->buffer[lexer->len] = var[i];
			lexer->len++;
			i++;
		}
		free(var);
	}
	else
	{
		var = shell_getenv(name, shell);
		if (var == NULL)
		{
			free(name);
			return ;
		}
		free(name);
		while (var[i])
		{
			lexer->buffer[lexer->len] = var[i];
			lexer->len++;
			i++;
		}
		free(var);
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
