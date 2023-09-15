/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:45:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/15 15:24:10 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_tok *token)
{
	char	*tmplimiter;
	char	*line;
	int		heredoc;

	tmplimiter = ft_strjoin(token->next->token, "\n");
	line = get_next_line(STDIN_FILENO);
	heredoc = open(HEREPATH, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (heredoc < 0)
		perror("heredoc");
	while (line)
	{
		if (!ft_strncmp(line, tmplimiter, ft_strlen(tmplimiter) + 1))
		{
			close(heredoc);
			free(tmplimiter);
			free(line);
			get_next_line(-42);
			heredoc = open(HEREPATH, O_RDONLY, 0666);
			return (heredoc);
		}
		ft_putstr_fd(line, heredoc);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	return (-1);
}

void	pars_redir(t_tok *token, int r, t_pars *command)
{
	if (ft_strncmp(token->token, ">", 2) == 0)
	{
		command->redirs[r] = OUTPUT;
		command->redir_name[r] = ft_strdup(token->next->token);
	}
	else if (ft_strncmp(token->token, ">>", 3) == 0)
	{
		command->redirs[r] = APPEND;
		command->redir_name[r] = ft_strdup(token->next->token);
	}
	else if (ft_strncmp(token->token, "<", 2) == 0)
	{
		command->redirs[r] = INPUT;
		command->redir_name[r] = ft_strdup(token->next->token);
	}
	else if (ft_strncmp(token->token, "<<", 3) == 0)
	{
		command->redirs[r] = HEREDOC;
		command->redir_name[r] = ft_strdup(token->next->token);
	}
}

void	pars_commander(t_tok *token, t_pars *command)
{
	int		i;
	int		n;
	int		r;
	t_tok	*tmp;

	n = 0;
	r = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIRECT)
		{
			if (tmp->next)
			{
				r++;
				tmp = tmp->next;
			}		
		}
		else
			n++;
		tmp = tmp->next;
	}
	command->cmds = (char **)ft_calloc(n + 1, sizeof(char *));
	if (r)
	{
		command->numred = r;
		command->redirs = (int *)ft_calloc(r, sizeof(int));
		command->redir_name = (char **)ft_calloc(r  + 1, sizeof(char *));
	}
	i = 0;
	r = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIRECT)
		{
			if (tmp->id == 1)
				command->exec = false;
			if (tmp->next)
			{
				pars_redir(tmp, r, command);
				r++;
				tmp = tmp->next;
			}
		}
		else
		{
			command->cmds[i] = ft_strdup(tmp->token);
			i++;
		}
		tmp = tmp->next;
	}
}

void	shell_parser(t_shell *shell, t_pars **command)
{
	t_tok		*token;
	static int	n;
	int			pipes;
	int			i;
	char		**inputs;

	*command = NULL;
	token = NULL;
	pipes = pipe_numstr(shell->input, '|');
	if (pipes == -1)
	{
		write(STDERR_FILENO, "syntax error near unexpected token", 35);
		ft_printf(" \"%c\"\n", '|');
		g_exit = 1;
		shell->exit = g_exit;
		return ;
	}
	if (pipes > 1)
		inputs = pipe_split(shell->input, '|');
	else
	{
		inputs = (char **)ft_calloc(2, sizeof(char *));
		inputs[0] = ft_strdup(shell->input);
		inputs[1] = NULL;
	}
	n = 0;
	i = 0;
	while (inputs[i])
	{
		lex_tokenizer(shell, inputs[i], &token, &n);
/* 		if (token == NULL || shell->exit == 1)
		{
			tok_free(token);
			continue ;
		} */
		pars_lstadd_back(command, pars_lstnew(i + 1));
		pars_commander(token, pars_lstlast(*command));
		tok_free(token);
		token = NULL;
		i++;
	}
	tok_free(token);
	lex_free_inputs(inputs);
}

void	pars_free(t_pars *command)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	while (command)
	{
		tmp = command;
		command = command->next;
		while (tmp->cmds[i])
			free(tmp->cmds[i++]);
		free(tmp->cmds);
		i = 0;
		if (tmp->redirs)
		{
			free(tmp->redirs);
			while(tmp->redir_name[i])
				free(tmp->redir_name[i++]);
			free(tmp->redir_name);
			i = 0;
		}
		free(tmp);
	}
}
