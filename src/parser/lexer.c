/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:22:06 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/23 04:01:02 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_type(char *s)
{
	if (ft_strncmp(s, ">", 2) == 0)
	{
		return (TRUNC);
	
	}
	else if (ft_strncmp(s, ">>", 3 == 0))
	{
		return (APPEND);

	}	
	else if (ft_strncmp(s, "<", 2) == 0)
	{
		return (INPUT);
	
	}
	else if (ft_strncmp(s, "<<", 3) == 0)
	{
		return (HEREDOC);
	
	}
	//	Check command too

	return (ARG);
}

void	lex_tokenizer(char *input, t_tok **token, int *id)
{
	t_lex	*lex;
	int		i;

	lex = (t_lex *)ft_calloc(1, sizeof(t_lex));
	lex->state = STATE_NORMAL;
	lex->len = 0;
	i = 0;
	while(input[i])
	{
		if (lex->state == STATE_NORMAL)
			state_normal(input[i], lex, token, id);
		else if (lex->state == STATE_DOUBLE_QUOTE || lex->state == STATE_SINGLE_QUOTE)
			state_quotes(input[i], lex, token, id);
		else if (lex->state == STATE_DOLLAR_SIGN)
			state_dollar(input[i], lex, token, id);
		else if (lex->state == STATE_DOLLAR_SIGN_DOUBLE_QUOTE)
			state_dollarquotes(input[i], lex, token, id);
		i++;
	}
	if (lex->len)
	{
		lex->buffer[lex->len] = '\0';
		if (lex->state == STATE_DOLLAR_SIGN)
		{
			if (numstr(lex->buffer, '$') > 1)
				lex_multiexpand(lex);
			else
				lex_expand(lex);
		}
		lex->buffer[lex->len] = '\0';
		lex_lstadd(token, lex, id);
	}
	lex_free(lex);
}

void	shell_lexer(t_shell *shell)
{
	static int	id;
	int			i;
	char		**inputs;
	t_tok		*token;

	token = NULL;
	if (pipe_numstr(shell->input, '|') > 1)
		inputs = pipe_split(shell->input, '|');
	else
	{
		inputs = (char **)ft_calloc(2, sizeof(char *));
		inputs[0] = ft_strdup(shell->input);
		inputs[1] = NULL;
	}
	id = 0;
	i = 0;
	while (inputs[i])
	{
		lex_tokenizer(inputs[i], &token, &id);
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
