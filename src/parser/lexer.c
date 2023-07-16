/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:18:44 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/16 22:50:24 by adi-nata         ###   ########.fr       */
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

			//lex->word[i] = '\0';
			//i = 0;
			lex->state = STATE_DOUBLE_QUOTE;
		}
		else
		{
			// Append space to current word inside quotes

			lex->word[i] = c;
			//i++;
		}
	}
	else if (c == DOUBLE_QUOTE)
	{
		// End of double quoted sequence

		lex->state = STATE_NORMAL;
		lex->in_quotes = false;
	}
	else/*  if (c == '$') */
	{
		// Escaped $ sign (and others) = treat it as regular char

		lex->word[i] = c;
		i++;
	}
	lex->len = i;
}

void	state_dollar(char c, t_lex *lex)
{
	int	i;

	i = lex->len;
	if (c == ' ')
	{
		if (!lex->in_quotes)
		{
			// End of variable name, append expanded value to current word

			lex->word[i] = '\0';
			lex->len = 0;
			lex->state = STATE_NORMAL;
		}
		else
		{
			// Append space to current word inside quotes

			lex->word[i] = c;
			//i++;
		}
	}
	else/*  if (c == '$') */
	{
		// Escaped $ sign (and others) = treat it as regular char

		lex->word[i] = c;
		//i++;
	}
	lex->len = i;
}

void	state_quotes(char c, t_lex *lex)
{
	int	i;

	i = lex->len;
	if (lex->state == STATE_DOUBLE_QUOTE)
	{
		if (c == DOUBLE_QUOTE)
		{
			// End of double quoted sequence

			lex->in_quotes = false;

		}
		else if (c == '$')
		{
			// Start expansion

			lex->state = STATE_DOLLAR_SIGN_DOUBLE_QUOTE;
		}
		else
		{
			// Append char to current word inside double quotes

			lex->word[i] = c;
			//i++;
		}
	}
	else if (lex->state == STATE_SINGLE_QUOTE)
	{
		if (c == SINGLE_QUOTE)
		{
			// End of single quoted sequence

			lex->in_quotes = false;

		}
		else
		{
			// Append char to current word inside single quotes

			lex->word[i] = c;
			//i++;
		}
	}
	lex->len = i;
}

void	state_normal(char c, t_lex *lex)
{
	int	i;

	i = lex->len;
	if (c == ' ')
	{
		if (!lex->in_quotes)
		{
			// End of word

			lex->word[i] = '\0';
			//i++;
			//i = 0;
		}
		else
		{
			// Append space in quoted sequence

			lex->word[i] = c;
			//i++;
		}
	}
	else if (c == DOUBLE_QUOTE)
	{
		if (lex->in_quotes)
		{
			// End of double quoted sequence

			lex->in_quotes = false;
		}
		else
		{
			// Start of double quoted sequence

			lex->state = STATE_DOUBLE_QUOTE;
			lex->in_quotes = true;
		}
	}
	else if (lex->state == SINGLE_QUOTE)
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

			lex->word[i] = c;
			i++;
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

			lex->word[i] = c;
			i++;
		}
	}
	else
	{
		// Append char to current word

		lex->word[i] = c;
		//i++;
	}		

	lex->len = i;
}

void	lex_tokenizer(const char *input)
{
	t_lex	lex;
	//int		i;

	lex.state = STATE_NORMAL;
	lex.len = 0;
	lex.word = ft_calloc(ft_strlen(input), sizeof(char));
	lex.in_quotes = false;
	//i = 0;
	while(input[lex.len])
	{
		if (lex.state == STATE_NORMAL)
			state_normal(input[lex.len], &lex);
		else if (lex.state ==  STATE_DOUBLE_QUOTE || lex.state == STATE_SINGLE_QUOTE)
			state_quotes(input[lex.len], &lex);
		else if (lex.state == STATE_DOLLAR_SIGN)
			state_dollar(input[lex.len], &lex);
		else if (lex.state == STATE_DOLLAR_SIGN_DOUBLE_QUOTE)
			state_dollarquotes(input[lex.len], &lex);
		printf("%c", lex.word[lex.len]);
		lex.len++;
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
