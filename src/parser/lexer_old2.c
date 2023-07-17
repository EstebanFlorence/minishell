/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:18:44 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/17 17:05:10 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_dollarquotes(char c, t_lex *lex)
{
	int	i;

	i = lex->len;
	if (c == ' ')
	{
		if (lex->in_quotes)
		{
			// End of variable name, append expaded value to current word

			lex->word[i] = '\0';
			lex->len = 0;
			lex->state = STATE_DOUBLE_QUOTE;
		}
		else
		{
			// Append space to current word inside quotes

			lex->word[lex->len] = c;
			lex->len++;
		}
	}
	else if (c == DOUBLE_QUOTE)
	{
		// End of double quoted sequence

		lex->in_quotes = false;
		lex->state = STATE_NORMAL;
	}
	else/*  if (c == '$') */
	{
		// Escaped $ sign (and others) = treat it as regular char

		lex->word[lex->len] = c;
		lex->len++;
	}
}

void	state_dollar(char c, t_lex *lex)
{
	if (c == ' ')
	{
		if (!lex->in_quotes)
		{
			// End of variable name, append expanded value to current word

			lex->word[lex->len] = '\0';
			lex->len = 0;
			lex->state = STATE_NORMAL;
		}
		else
		{
			// Append space to current word inside quotes

			lex->word[lex->len] = c;
			lex->len++;
		}
	}
	else/*  if (c == '$') */
	{
		// Escaped $ sign (and others) = treat it as regular char

		lex->word[lex->len] = c;
		lex->len++;
	}
}



void	state_quotes(char c, t_lex *lex)
{
	if (lex->state == STATE_DOUBLE_QUOTE)
	{
		if (c == DOUBLE_QUOTE)
		{
			// End of double quoted sequence

			lex->in_quotes = false;
			//lex->state = STATE_NORMAL;
		}
		else if (c == ' ')
		{
			// Space after end of double quoted sentence

			lex->state = STATE_NORMAL;
		}
		else if (c == '$')
		{
			// Start expansion

			lex->state = STATE_DOLLAR_SIGN_DOUBLE_QUOTE;
		}
		else
		{
			// Append char to current word inside double quotes

			lex->word[lex->len] = c;
			lex->len++;
		}
	}
	else if (lex->state == STATE_SINGLE_QUOTE)
	{
		if (c == SINGLE_QUOTE)
		{
			// End of single quoted sequence

			lex->in_quotes = false;
			//lex->state = STATE_NORMAL
		}
		else if (c == ' ')
		{
			// Space after end of single quoted sentence

			lex->state = STATE_NORMAL;
		}
		else
		{
			// Append char to current word inside single quotes

			lex->word[lex->len] = c;
			lex->len++;
		}
	}
}

void	state_normal(char c, t_lex *lex)
{
	if (c == ' ')
	{
		if (!lex->in_quotes)
		{
			// End of word

			if (lex->len > 0)
			{
				lex->word[lex->len] = '\0';
				
				lex->len = 0;
			}
		}
		else
		{
			// Append space in quoted sequence

			lex->word[lex->len] = c;
			lex->len++;
		}
	}
	else if (c == DOUBLE_QUOTE)
	{
		if (lex->in_quotes)
		{
			// End of double quoted sequence

			lex->in_quotes = false;
			//lex->state = STATE_NORMAL;
		}
		else
		{
			// Start of double quoted sequence

			lex->state = STATE_DOUBLE_QUOTE;
			lex->in_quotes = true;
		}
	}
	else if (c == SINGLE_QUOTE)
	{
		if (!lex->in_quotes)
		{
			// Start of single quoted sequence

			lex->state = STATE_SINGLE_QUOTE;
			lex->in_quotes = true;
		}
		else
		{
			// Append single quote to current word inside quotes

			lex->word[lex->len] = c;
			lex->len++;
		}

	}
	else if (c == '$')
	{
		// lex_expander()? sia dentro che fuori quotes
		if (!lex->in_quotes)
		{
			// Start expansion

			lex->state = STATE_DOLLAR_SIGN;
		}
		else
		{
			// Append $ sign to current word inside quotes

			lex->word[lex->len] = c;
			lex->len++;
		}
	}
	else
	{
		// Append char to current word

		lex->word[lex->len] = c;
		lex->len++;
	}		
}

void	lex_tokenizer(const char *input)
{
	t_lex	lex;
	int		i;

	lex.state = STATE_NORMAL;
	lex.len = 0;
	lex.word = ft_calloc(ft_strlen(input), sizeof(char));
	lex.in_quotes = false;
	i = 0;
	while(input[i])
	{
		if (lex.state == STATE_NORMAL)
			state_normal(input[i], &lex);
		else if (lex.state ==  STATE_DOUBLE_QUOTE || lex.state == STATE_SINGLE_QUOTE)
			state_quotes(input[i], &lex);
		else if (lex.state == STATE_DOLLAR_SIGN)
			state_dollar(input[i], &lex);
		else if (lex.state == STATE_DOLLAR_SIGN_DOUBLE_QUOTE)
			state_dollarquotes(input[i], &lex);
		printf("%c", lex.word[i]);
		i++;
	}
	if (lex.len)
		lex.word[lex.len] = '\0';
	printf("\nword: %s\n", lex.word);
	free(lex.word);
	//char **words = ft_split(lex.word, '\0');
	//for (int i = 0; words[i]; i++)
	//	printf("word: %s\n", words[i]);
	//free(words);
}

void	shell_lexer(t_shell *shell, t_tok **lexer)
{
	lex_tokenizer(shell->input);


	t_tok *tmp = *lexer;
	while (tmp)
	{
		printf("lexer id: %d type: %d token: %s\n", tmp->id, tmp->type, tmp->token);
		tmp = tmp->next;
	}
}
