/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:51:23 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/11 21:01:58 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_lstadd(t_parser **parser, char *s)
{
	static int	i;

	i = 0;
	pars_lstadd_back(parser, pars_lstnew(s, i));
	i++;
}

t_lexer	*pars_starter(t_lexer *lexer)
{
	t_lexer	*index;

	index = lexer;
	while(index->prev)
		index = index->prev;
	return (index);
}

void	pars_commander(t_lexer *lexer, t_parser **parser)
{
	t_lexer	*index;
	char	*command;
	char	*tmp;

	index = pars_starter(lexer);
	command = ft_strdup(index->token);
	while (index->id < lexer->id)
	{
		if (index->next->id < lexer->id )
		{
			tmp = ft_strjoin(command, " ");
			free(command);
			command = ft_strjoin(tmp, index->next->token);
			free(tmp);
		}
		index = index->next;
	}
	printf("command: %s\n", command);
	pars_lstadd(parser, command);
	free(command);
}

void	pars_checker(t_lexer **lexer, t_parser **parser)
{
	t_lexer		*index;

	index = *lexer;
	while (index)
	{
		if (ft_strncmp(index->token, "<", 2) == 0)
		{
			printf("redirection\n");
			//pars_commander(*lexer);
		}
		else if (ft_strncmp(index->token, ">", 2) == 0)
		{
			printf("redirection\n");
			//pars_commander(*lexer);
		}
		else if (ft_strncmp(index->token, "<<", 3) == 0)
		{
			printf("redirection\n");
			//pars_commander(*lexer);
		}
		else if (ft_strncmp(index->token, ">>", 3 == 0))
		{
			printf("redirection\n");
			//pars_commander(*lexer);
		}
		else if (ft_strncmp(index->token, "|", 2) == 0)
		{
			printf("pipe\n");
			pars_commander(index, parser);
		}
		else if (ft_strncmp(index->token, "$", 2) == 0)
		{
			printf("env / expander?\n");
			//pars_commander(*lexer);
		}
		//else if (ft_strncmp(index->token, "||", 3) == 0)
		//	printf("bonus\n");
		//else if (ft_strncmp(index->token, "&&", 3) == 0)
		//	printf("bonus\n");

		index = index->next;
	}
}

void	ft_parser(t_shell *shell)
{
	t_lexer		*lexer;
	t_parser	*parser;

	lexer = NULL;
	parser = NULL;
	ft_lexer(shell, &lexer);
	pars_checker(&lexer, &parser);

	lex_free(lexer);
}

void	pars_free(t_parser *parser)
{
	t_parser	*tmp;

	while (parser)
	{
		tmp = parser;
		parser = parser->next;
		free(tmp->token);
		free (tmp);
	}
}


/* 
void	pipe_split(t_shell *shell, t_lexer *lexer)
{
	char	**commands;

	commands = ft_split(shell->input, '|');

}

void	pars_checker(t_lexer **lexer, t_parser **parser)
{

}
*/
/*
 int	pars_finder(t_lexer *lexer)
{
	t_lexer	*index;

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