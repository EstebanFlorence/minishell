/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:45:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/27 19:50:23 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_commander(t_shell *shell, t_pars **parser, t_tok *token)
{
	t_tok	*tmp;
	char	*spaced;
	char	*tmp_cmd1;
	char	*tmp_cmd2;
	char	*cmd;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			tmp_cmd1 = ft_strdup(tmp->token);
			tmp = tmp->next;
			while (tmp && tmp->type == ARG)
			{
				spaced = ft_strjoin(" ", tmp->token);
				tmp_cmd2 = ft_strjoin(tmp_cmd1, spaced);
				free(spaced);
				tmp = tmp->next;
			}
			if (spaced)
				free(spaced);
		}
		tmp = tmp->next;
	}

}

void	shell_parser(t_shell *shell, t_pars **parser)
{
	t_tok	*token;

	(void)parser;
	token = NULL;
	shell_lexer(shell, &token);

	//pars_commander(shell, parser, token);

	tok_free(token);
}
