/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:50:06 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/19 22:54:05 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_multiexpand_putvar(t_exp *exp, t_lex *lexer)
{
	int	i;

	i = 0;
	while (exp->expanded[i])
	{
		lexer->buffer[lexer->len] = exp->expanded[i];
		lexer->len++;
		i++;
	}
}

void	lex_multiexpand_var(t_exp *exp)
{
	char	*tmp;

	tmp = exp->expanded;
	exp->expanded = ft_strjoin(tmp, exp->var);
	free(tmp);
}

void	lex_multiexpand_status(int i, t_exp *exp)
{
	char	*tmp;

	exp->status = exp_status(exp->expandables[i]);
	tmp = exp->expanded;
	exp->expanded = ft_strjoin(tmp, exp->status);
	free(exp->status);
	free(tmp);
}

void	lex_expand_var(char *name, t_lex *lexer, t_shell *shell)
{
	int		i;
	char	*var;

	i = 0;
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

void	lex_expand_status(char *name, t_lex *lexer)
{
	int		i;
	char	*var;

	i = 0;
	var = exp_status(name);
	free(name);
	while (var[i])
	{
		lexer->buffer[lexer->len] = var[i];
		lexer->len++;
		i++;
	}
	free(var);
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
