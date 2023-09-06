/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:22:06 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/05 22:40:39 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(const char *cmd, t_shell *shell)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (shell->paths[i])
	{
		cmd_path = ft_strjoin(shell->paths[i], cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free(cmd_path);
			return (1);
		}
		free(cmd_path);
		i++;
	}
	return (0);
}

int	lex_type(const char *s, t_shell *shell)
{
	if (ft_strlen(s) < 1)
		return (EMPTY);
/* 	else if (ft_strncmp(s, ">", 2) == 0 || ft_strncmp(s, ">>", 3) == 0 ||
			ft_strncmp(s, "<", 2) == 0 || ft_strncmp(s, "<<", 3) == 0)
		return (REDIRECT); */
 	else if (is_command(s, shell))
		return (CMD);
	return (ARG);
}

void	lex_tokenizer(t_shell *shell, char *input, t_tok **token, int *id)
{
	t_lex	*lex;
	int		i;

	lex = (t_lex *)ft_calloc(1, sizeof(t_lex));
	lex->state = STATE_NORMAL;
	lex->type = -1;
	lex->len = 0;
	lex->shell = shell;
	i = 0;
	while(input[i] && lex->type != -2)
	{
		if (lex->state == STATE_NORMAL)
			state_normal(input[i], lex, token, id);
		else if (lex->state == STATE_DOUBLE_QUOTE || lex->state == STATE_SINGLE_QUOTE)
			state_quotes(input[i], lex);
		else if (lex->state == STATE_DOLLAR_SIGN)
			state_dollar(input[i], lex, token, id);
		else if (lex->state == STATE_DOLLAR_SIGN_DOUBLE_QUOTE)
			state_dollarquotes(input[i], lex, token, id);
		else if (lex->state == STATE_REDIRECT)
			state_redirect(input[i], lex, token, id);
		i++;
	}
	if (lex->type == -2)
	{
		exit_status = 2;
		shell->exit = exit_status;
	}
	else if (lex->len)
	{
		lex->buffer[lex->len] = '\0';
		if (lex->state == STATE_DOLLAR_SIGN)
		{
			if (numstr(lex->buffer, '$') > 1)
				lex_multiexpand(lex);
			else
				lex_expand(lex);
		}
		lex->buffer[lex->len] = '\0';
		tok_lstadd(token, lex, id);
	}
	free(lex);
}

void	lex_free_inputs(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		free(inputs[i]);
		inputs[i] = NULL;
		i++;
	}
	free(inputs);
}

void	tok_free(t_tok *token)
{
	t_tok	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->token); 
		free(tmp);
	}
}
