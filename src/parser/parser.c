/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:51:23 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/10 18:22:39 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	parser(t_lexer **lexer)
{
	t_lexer	*index;

	index = *lexer;
	while (index)
	{
		if (ft_strncmp(index->token, "<", 2))
		{
			printf("redirection\n");

		}
		else if (ft_strncmp(index->token, ">", 2))
		{
			printf("redirection\n");

		}
		else if (ft_strncmp(index->token, "<<", 3))
		{
			printf("redirection\n");

		}
		else if (ft_strncmp(index->token, ">>", 3))
		{
			printf("redirection\n");
			
		}
		else if (ft_strncmp(index->token, "|", 2))
		{
			printf("pipe\n");
		}
		else if (ft_strncmp(index->token, "$", 2))
		{
			printf("env / expander?\n");

		}
		//else if (ft_strncmp(index->token, "||", 3))
		//	printf("bonus\n");
		//else if (ft_strncmp(index->token, "&&", 3))
		//	printf("bonus\n");

		index = index->next;
	}
}
