/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:22:06 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/17 18:37:55 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_piper(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		
		i++;
	}
}

void	shell_lexer(t_shell *shell, t_tok **lexer)
{
	char	**piped;

	piped = shell_split(shell->input, '|');
	if (piped != NULL)
		lex_piper(piped);


/* 	t_tok *tmp = *lexer;
	while (tmp)
	{
		printf("lexer id: %d type: %d token: %s\n", tmp->id, tmp->type, tmp->token);
		tmp = tmp->next;
	} */
}
