/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 23:11:15 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/02 16:39:41 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	status_putvar(char *var, char *exp, int *i, int *j)
{
	while (var[*j])
	{
		exp[*i] = var[*j];
		(*i)++;
		(*j)++;
	}
}

void	status_putstat(char *status, char *exp, int *i)
{
	while (status[*i])
	{
		exp[*i] = status[*i];
		(*i)++;
	}
}

char	*exp_status(char *var)
{
	int		i;
	int		j;
	char	*exp;
	char	*status;

	i = 0;
	j = is_status(var);
	status = ft_itoa(g_exit);
	if (ft_strlen(var) > 1)
	{
		if (j == 0)
		{
			exp = ft_calloc((ft_strlen(var) + ft_strlen(status) + 1),
					sizeof(char));
			status_putstat(status, exp, &i);
			j = 1;
		}
		else
			exp = ft_calloc((ft_strlen(var) - j + 1), sizeof(char));
		status_putvar(var, exp, &i, &j);
		free(status);
		return (exp);
	}
	return (status);
}

void	lex_multiexpand(t_lex *lexer, t_shell *shell)
{
	int		i;
	t_exp	*exp;

	i = 0;
	exp = (t_exp *)ft_calloc(1, sizeof(t_exp));
	exp->names = ft_substr(lexer->buffer, lexer->start, lexer->len);
	exp->expandables = ft_split(exp->names, '$');
	exp->expanded = ft_strdup("");
	while (exp->expandables[i])
	{
		exp->var = shell_getenv(exp->expandables[i], shell);
		if (is_status(exp->expandables[i]) >= 0)
			lex_multiexpand_status(i, exp);
		else if (exp->var != NULL)
			lex_multiexpand_var(exp);
		free(exp->var);
		i++;
	}
	lex_bzero(lexer->buffer, lexer->start - 1, (lexer->len - lexer->start));
	lexer->len = lexer->start - 1;
	lex_multiexpand_putvar(exp, lexer);
	lex_expand_free(exp);
}

void	lex_expand(t_lex *lexer, t_shell *shell)
{
	char	*name;

	if (lexer->len == 1)
		return ;
	name = ft_substr(lexer->buffer, lexer->start, (lexer->len - lexer->start));
	lex_bzero(lexer->buffer, lexer->start - 1, lexer->len);
	lexer->len = lexer->start - 1;
	if (is_status(name) >= 0)
		lex_expand_status(name, lexer);
	else
		lex_expand_var(name, lexer, shell);
}
