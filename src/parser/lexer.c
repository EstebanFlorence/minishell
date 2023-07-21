/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:22:06 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/21 19:07:31 by adi-nata         ###   ########.fr       */
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
	else if (ft_strncmp(s, "|", 2) == 0)
	{
		return (PIPE);
	}
/* 	else if (ft_strchr(s, '$') && is_expandable(s) == 1)
	{
		return (EXPAND);
	} */
	return (CMD);
}


void	state_dollarquotes(char c, t_lex *lex, t_tok **token)
{
	if (c == ' ')
	{
			// End of variable name, append expanded value to current word
			if (lex->len > 0)
			{
				lex->buffer[lex->len] = '\0';
				// Expand
				lex_expand(lex->buffer);
				lex_lstadd(token, lex);
				lex->len = 0;
				lex->state = STATE_DOUBLE_QUOTE;
			}

			// Append space to quoted sequence
			else
			{
				lex->buffer[lex->len] = c;
				lex->len++;
				lex->state = STATE_DOUBLE_QUOTE;
			}
	}
	else if (c == DOUBLE_QUOTE)
	{
		// End of double quoted sequence and variable name, append expanded value to current word

		if (lex->len > 0)
		{
			lex->buffer[lex->len] = '\0';
			lex->len = 0;
			// Expand
			lex_expand(lex->buffer);
			lex_lstadd(token, lex);
			lex->state = STATE_NORMAL;
		}
		else
			lex->state = STATE_NORMAL;
	}
	else/*  if (c == '$') */
	{
		// Escaped $ sign (and others) = treat it as regular char

		lex->buffer[lex->len] = c;
		lex->len++;
	}
}

void	state_dollar(char c, t_lex *lex, t_tok **token)
{
	if (c == ' ')
	{
		// End of variable name, append expanded value to current word

		if (lex->len > 0)
		{
			lex->buffer[lex->len] = '\0';
			// Expand
			lex_expand(lex->buffer);
			lex_lstadd(token, lex);
			lex->len = 0;
			lex->state = STATE_NORMAL;
		}
			
	}

	//	Not interpret unclosed quotes or special characters which are not required by the
	//	subject such as \ (backslash) or ; (semicolon).
	// 	Escaped '\$' sign: expand previous variable and append
	//	es. $USER\$ER -> esteban$ER |
	//		$U\$ER -> $ER | $\$USER\$ ->  $$USER$

	else if (c == '$')
	{
		if (lex->len > 0 && lex->buffer[lex->len - 1] == '\\')
		{

/* 			lex->buffer[lex->len - 1] = '$';
			lex->buffer[lex->len] = '\0';
			lex_lstadd(token, lex);
			lex->len = 0;
			lex->state = STATE_NORMAL; */

			lex->buffer[lex->len - 1] = '\0';
			lex_expand(lex->buffer);
			
			lex->len = ft_strlen(lex->buffer);
			lex->buffer[lex->len] = '$';
			lex->len++;
			lex->state = STATE_NORMAL;
			//lex->buffer[lex->len] = '\0';

		}

		// '$' in var name, keep appending

		else
		{
			lex->buffer[lex->len] = c;
			lex->len++;
		}
	}

	else
	{
		// Escaped $ sign (and others) = treat it as regular char

		lex->buffer[lex->len] = c;
		lex->len++;
	}
}


void	lex_tokenizer(char *input, t_tok **token)
{
	t_lex	*lex;
	int		i;

	lex = (t_lex *)ft_calloc(1, sizeof(t_lex));
	lex->state = STATE_NORMAL;
	lex->len = 0;
	//lex->buffer = ft_calloc(ft_strlen(input), sizeof(char));
	i = 0;
	while(input[i])
	{
		if (lex->state == STATE_NORMAL)
			state_normal(input[i], lex, token);
		else if (lex->state == STATE_DOUBLE_QUOTE || lex->state == STATE_SINGLE_QUOTE)
			state_quotes(input[i], lex, token);
		else if (lex->state == STATE_DOLLAR_SIGN)
			state_dollar(input[i], lex, token);
		else if (lex->state == STATE_DOLLAR_SIGN_DOUBLE_QUOTE)
			state_dollarquotes(input[i], lex, token);
		i++;
	}
	if (lex->len)
	{
		lex->buffer[lex->len] = '\0';
		if (lex->state == STATE_DOLLAR_SIGN)
			lex_expand(lex->buffer);
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
		inputs = (char **)ft_calloc(2, sizeof(char *));
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

	//lex_dollar(&token);

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
