/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:00:46 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/11 21:39:31 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lexer(t_shell *shell, t_lexer **lexer)
{
	shell->inputs = ft_split(shell->input, ' ');
	lex_innit(shell, lexer);
	t_lexer *tmp = *lexer;
	while (tmp)
	{
		printf("lexer id: %d token: %s\n", tmp->id, tmp->token);
		tmp = tmp->next;
	}
}

int	lex_wordscount(char *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && s[i] != ' ')
		{
			if (s[i + 1] == ' ' || !s[i + 1])
				words++;
			i++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (words);
}

void	lex_remove(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer;
		lexer = lexer->prev;
		free (tmp);
	}
}

void	lex_free(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer;
		lexer = lexer->next;
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