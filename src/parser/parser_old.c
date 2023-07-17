/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:51:23 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/16 18:16:14 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_commander(t_tok *start, t_tok *end, t_pars **parser)
{
	char	*command;
	char	*tmp;

	command = ft_strdup(start->token);
	while (start->id < end->id)
	{
		if (start->next->id < end->id || !end->next)
		{
			tmp = ft_strjoin(command, " ");
			free(command);
			command = ft_strjoin(tmp, start->next->token);
			free(tmp);
		}
		start = start->next;
	}

	printf("command: %s\n", command);
	pars_lstadd(parser, command);
	free(command);
}

void	shell_parser(t_shell *shell, t_pars **parser)
{
	t_tok	*lexer;

	(void)parser;
	lexer = NULL;
	shell_lexer(shell, &lexer);
//	if (strchr_index(shell->input, '|'))
//		pars_piper(&lexer, parser);
//	pars_redirect(&lexer, &parser);
//	parse_inout();

/* 	t_pars *tmp = *parser;
	while (tmp)
	{
		printf("parser id: %d\tcommand: %s\n", tmp->id, tmp->token);
		tmp = tmp->next;
	} 
*/

	//lex_free(lexer);
	//pars_free(*parser);
}

void	pars_free(t_pars *parser)
{
	t_pars	*tmp;

	while (parser)
	{
		tmp = parser;
		parser = parser->next;
		free(tmp->token);
		free (tmp);
	}
}

void	pars_lstadd(t_pars **parser, char *s)
{
	static int	i = 0;

	pars_lstadd_back(parser, pars_lstnew(s, i));
	i++;
}




/* 
void	pipe_split(t_shell *shell, t_tok *lexer)
{
	char	**commands;

	commands = ft_split(shell->input, '|');

}

void	pars_checker(t_tok **lexer, t_pars **parser)
{

}
*/
/*
 int	pars_finder(t_tok *lexer)
{
	t_tok	*index;

	index = lexer;
	while (index)
	{
		if (ft_strncmp(index->token, "<", 2) == 0)
			return (index->id + 1);
		else if (ft_strncmp(index->token, ">", 2) == 0)
			return (index->id + 1);
		else if (ft_strncmp(index->token, "<<", 3) == 0)
			return (index->id + 1);
		else if (ft_strncmp(index->token, ">>", 3 == 0))
			return (index->id + 1);
		else if (ft_strncmp(index->token, "|", 2) == 0)
			return (index->id + 1);
		else if (ft_strncmp(index->token, "$", 2) == 0)
			return (index->id);

	//	else if (uno stop acceso precedentemente es. fine stringa attaccata a $?)
	//	else if(ft_strchr(index->token, '$'))
	//		return (index->id + 1);

		index = index->prev;
	}
	return (0);
} */