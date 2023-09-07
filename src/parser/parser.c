/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:45:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/07 19:52:11 by adi-nata         ###   ########.fr       */
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

void	pars_redirect(t_tok *token, t_pars *command, t_shell *shell)
{
	//char	*file;

	//file = ft_strjoin(FILESPATH, token->next->token);
	if (ft_strncmp(token->token, ">", 2) == 0)
	{
		command->out = open(token->next->token, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (command->out < 0)
		{
			perror(token->next->token);
			exit_status = 1;
			shell->exit = exit_status;
		}
	}
	else if (ft_strncmp(token->token, ">>", 3) == 0)
	{
		command->out = open(token->next->token, O_CREAT | O_WRONLY | O_APPEND, 0666);
		if (command->out < 0)
		{
			perror(token->next->token);
			exit_status = 1;
			shell->exit = exit_status;
		}
	}
	else if (ft_strncmp(token->token, "<", 2) == 0)
	{
		command->in = open(token->next->token, O_RDONLY);
		if (command->in < 0)
		{
			perror(token->next->token);
			exit_status = 1;
			shell->exit = exit_status;
		}
	}
	else if (ft_strncmp(token->token, "<<", 3) == 0)
	{
		command->in = here_doc(token);
	}
	//free(file);
}

void	pars_commander(t_tok *token, t_pars *command, t_shell *shell)
{
	int		i;
	int		n;
	t_tok	*tmp;

	tmp = token;
	n = 0;
	while (tmp)
	{
		if (tmp->type == REDIRECT)
		{
			if (tmp->next)
				tmp = tmp->next;	
		}
		else
			n++;
		tmp = tmp->next;
	}
	command->cmds = (char **)ft_calloc(n + 1, sizeof(char *));
	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIRECT)
		{
			pars_redirect(tmp, command, shell);
			if (tmp->next)
				tmp = tmp->next;
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
	int			i;
	char		**inputs;

	*command = NULL;
	token = NULL;
	if (pipe_numstr(shell->input, '|') > 1)
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
		if (token == NULL || shell->exit == 1)
			break ;
		pars_lstadd_back(command, pars_lstnew(i + 1));
		pars_commander(token, pars_lstlast(*command), shell);
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
		i = 0;
		free(tmp->cmds);
		free(tmp);
	}
}
