/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:00:46 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/09 23:39:53 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lex_lstnew(int i, char *s)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer) * 1);
	if (new == NULL)
		return (NULL);
	new->id = i + 1;
	new->token = s;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*lex_lstlast(t_lexer *lexer)
{
	t_lexer	*next;

	if (lexer != NULL)
	{
		next = lexer;
		while (1)
		{
			if (next->next == NULL)
				return (next);
			next = next->next;
		}
	}
	return (NULL);
}

void	lex_lstadd_back(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*last;

	if (!lexer)
		return ;
	if (*lexer == NULL)
		*lexer = new;
	else
	{
		last = lex_lstlast(*lexer);
		if (last != NULL)
		{
			last->next = new;
			new->prev = last;
		}
	}
}

void	lexer_innit(t_shell *shell, t_lexer **lexer)
{
	int	i;

	i = -1;
	while (++i < shell->words)
		lex_lstadd_back(lexer, lex_lstnew(i, shell->inputs[i]));
}

void	ft_builder(t_shell *shell)
{
	t_lexer	*lexer;

	lexer = NULL;
	shell->words = ft_wordscount(shell->input);
	printf("ft_wordscount: %d\n", shell->words);

	shell->inputs = ft_split(shell->input, ' ');
	for (int i = 0; i < shell->words; i++)
		printf("%s\n", shell->inputs[i]);

	lexer_innit(shell, &lexer);
	t_lexer *tmp = lexer;
	while (tmp)
	{
		printf("lexer %d token: %s\n", tmp->id, tmp->token);
		tmp = tmp->next;
	}
	free(tmp);
	lex_free(lexer);


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

int	ft_wordscount(char *s)
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