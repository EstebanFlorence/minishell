/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:51:23 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/13 14:49:34 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_lstadd(t_pars **parser, char *s)
{
	static int	i = 0;

	pars_lstadd_back(parser, pars_lstnew(s, i));
	i++;
}



void	pars_commander(t_lex *start, t_lex *end, t_pars **parser)
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

void	pars_piper(t_lex **lexer, t_pars **parser)
{
	t_lex	*index;

	index = (*lexer);
	while (index)
	{
		if (ft_strncmp(index->token, "|", 2) == 0)
		{
			printf("pipe:\n");
			pars_commander((*lexer), index, parser);
			lex_remove(*lexer, index);
			(*lexer) = index;
		}
		if (!index->next)
		{
			printf("end:\n");
			pars_commander((*lexer), index, parser);
		}
		index = index->next;
	}

}

void	ft_pars(t_shell *shell)
{
	t_lex	*lexer;
	t_pars	*parser;

	lexer = NULL;
	parser = NULL;
	ft_lex(shell, &lexer);
//	if (ft_strnstr(shell->input, "|", 2))
	pars_piper(&lexer, &parser);
//	pars_redirect(&lexer, &parser);
//	parse_inout();

	t_pars *tmp = parser;
	while (tmp)
	{
		printf("parser id: %d\tcommand: %s\n", tmp->id, tmp->token);
		tmp = tmp->next;
	}

	lex_free(lexer);
	pars_free(parser);
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


/* 
t_lex	*pars_starter(t_lex *lexer)
{
	t_lex	*index;

	index = lexer;
	while(index->prev)
	{
		if (ft_strncmp(index->token, "|", 2) == 0)
			return (index->next);
		index = index->prev;
	}
	return (index);
} */
/* void	pars_checker(t_lex **lexer, t_pars **parser)
{
	t_lex		*index;

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
			if (index->prev)
				lex_remove(index->prev);
			(*lexer) = index;
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

		//printf("pars_checker id: %d\n", index->id);

		index = index->next;
	}
} */

/* 
void	pipe_split(t_shell *shell, t_lex *lexer)
{
	char	**commands;

	commands = ft_split(shell->input, '|');

}

void	pars_checker(t_lex **lexer, t_pars **parser)
{

}
*/
/*
 int	pars_finder(t_lex *lexer)
{
	t_lex	*index;

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