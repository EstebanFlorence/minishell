/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_old.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:00:46 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/18 19:40:45 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_input()
{

}
void	shell_lexer(t_shell *shell, t_tok **lexer)
{
	lex_wordscount(shell->input);

	//shell->inputs = ft_split(shell->input, ' ');
	//shell->inputs = lex_start(shell->input);
	//lex_innit(shell, lexer);
	t_tok *tmp = *lexer;
	while (tmp)
	{
		printf("lexer id: %d type: %d token: %s\n", tmp->id, tmp->type, tmp->token);
		tmp = tmp->next;
	}
}

int	quotes_end(char *s, int i, char quote)
{
	while (s[i++])
	{
		if (s[i] == quote)
			return(i);
	}	
	return (-1);
}

int	lex_quotes(char *s, int i)
{
	int		j;

	j = quotes_end(s, i, s[i]);
	if (!j)
		return (i);
	s[i] = '\0';
	s[j] = '\0';
	return (j);
}

int	lex_wordscount(char *s)
{
	int		i;
	//int		j;
	//int		words;
	//char	*delim;

	i = 0;
	//j = 0;
	//words = 0;
	//delim = " \'\"$";
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
		{
			s[i] = '\0';
			i++;
		}
		while (s[i] && s[i] != ' ')
		{
			if ((s[i] == '\"' || s[i] == '\'')/*  &&
				quotes_end(s, &j, s[i]) */)
			{
				i = lex_quotes(s, i);
/* 				words++;
				i = j;
				printf("i after quotes: %d\n", i);
				if (s[i + 1] == '\0')
					break; */
			}
			if (s[i + 1] == '\0' || s[i + 1] == ' ')
			{
				
			}

			i++;		
		}
	}
}

void	lex_remove(t_tok *start, t_tok *end)
{
	t_tok	*tmp;

	while (start->id < end->id)
	{
		tmp = start;
		start = start->next;
		free(tmp);
	}
}

void	tok_free(t_tok *token)
{
	t_tok	*tmp;

	while (lexer)
	{
		tmp = token;
		token = token->next;
		free (tmp);
	}
}

/* 
    Display a promt while waiting for a new commmand.
    Have a working history.
    Find and launch executables (using the PATH variable or an absolute path).
    Handle ' (single) and " (double) quotes like in bash.
    Implement redirections such as:
        < redirect input.
        > redirect output.
        << heredoc (doesn't affect history).
        >> redirect output in append mode.
    Implement | (pipes).
    Handle environment variables.
    Handle $?.
    ctrl-C, ctrl-D, and ctrl-\ should behave like in bash.
    Recreate the following builtins:
        echo with option -n.
        cd with only a relative or absolute path.
        pwd (no flags).
        export (no flags).
        unset (no flags).
        env (no flags or arguments).
        exit (no flags).
 */