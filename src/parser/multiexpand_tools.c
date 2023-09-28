/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiexpand_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:48:32 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/28 18:49:22 by adi-nata         ###   ########.fr       */
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
