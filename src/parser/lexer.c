/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:22:06 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/19 19:18:24 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_normal(char c, t_lex *lex, t_tok **token)
{
	if (c == ' ')
	{
		state_normal_space(c, lex, token);
	}
	else if (c == DOUBLE_QUOTE)
	{
		state_normal_dquote(lex);
	}
	else if (c == SINGLE_QUOTE)
	{
		state_normal_squote(lex);
	}
	else
	{
		// Append char to current word

		lex->word[lex->len] = c;
		lex->len++;
	}		
}

void	lex_tokenizer(char *input, t_tok **token)
{
	t_lex	*lex;
	int		i;

	lex = (t_lex *)ft_calloc(1, sizeof(t_lex));
	lex->state = STATE_NORMAL;
	lex->start = 0;
	lex->len = 0;
	lex->word = ft_calloc(ft_strlen(input), sizeof(char));
	lex->in_quotes = false;
	i = 0;
	while(input[i])
	{
		if (lex->state == STATE_NORMAL)
			state_normal(input[i], lex, token);
		else if (lex->state == STATE_DOUBLE_QUOTE || lex->state == STATE_SINGLE_QUOTE)
			state_quotes(input[i], lex);
		i++;
	}
	if (lex->len)
	{
		lex->word[lex->len] = '\0';
		lex_lstadd(token, lex);
	}
	lex_free(lex);

}

void	shell_lexer(t_shell *shell)
{
	t_tok	*token;
	int		i;
	char	**inputs;

	token = NULL;
	i = 0;
	if (pipe_numstr(shell->input, '|') > 1)
		inputs = pipe_split(shell->input, '|');
	else
	{
		inputs = (char **)ft_calloc(1, sizeof(char *));
		inputs[0] = ft_strdup(shell->input);
		inputs[1] = NULL;
	}
	while (inputs[i])
	{
		lex_tokenizer(inputs[i], &token);
		i++;
	}

	t_tok *tmp = token;
	while (tmp)
	{
		printf("token id: %d type: %d token: %s\n", tmp->id, tmp->type, tmp->token);
		tmp = tmp->next;
	}

	lex_free_inputs(inputs);
	tok_free(token);
}

void	lex_free_inputs(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		free(inputs[i]);
		inputs[i] = NULL;
		i++;
	}
	free(inputs);
}

void	lex_free(t_lex *lexer)
{
	free(lexer->word);
	free(lexer->token);
	free(lexer);
}

void	tok_free(t_tok *token)
{
	t_tok	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->token); 
		free(tmp);
	}
}
