/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:45:03 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/06 19:09:39 by adi-nata         ###   ########.fr       */
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

void	pars_redirect(t_tok *token, t_pars *command)
{
	//char	*file;

	//file = ft_strjoin(FILESPATH, token->next->token);
	if (ft_strncmp(token->token, ">", 2) == 0)
	{
		command->out = open(token->next->token, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (command->out < 0)
			perror(token->next->token);
	}
	else if (ft_strncmp(token->token, ">>", 3) == 0)
	{
		command->out = open(token->next->token, O_CREAT | O_WRONLY | O_APPEND, 0666);
		if (command->out < 0)
			perror(token->next->token);
	}
	else if (ft_strncmp(token->token, "<", 2) == 0)
	{
		command->in = open(token->next->token, O_RDONLY);
		if (command->in < 0)
			perror(token->next->token);
	}
	else if (ft_strncmp(token->token, "<<", 3) == 0)
	{
		command->in = here_doc(token);
	}
	//free(file);
}

void	pars_commander(t_tok *token, t_pars *command)
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
	command->cmd = (char **)ft_calloc(n + 1, sizeof(char *));
	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIRECT)
		{
			pars_redirect(tmp, command);
			if (tmp->next)
				tmp = tmp->next;
		}
		else
		{
			command->cmd[i] = ft_strdup(tmp->token);
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
		pars_commander(token, pars_lstlast(*command));
		tok_free(token);
		token = NULL;
		i++;
	}
	tok_free(token);
	lex_free_inputs(inputs);
}

/* void	shell_command(t_shell *shell, t_pars **command)
{
	shell_command(shell, command);

	int i = 0;
	t_pars *tmpp = *command;
	while (tmpp)
	{
		while (tmpp->cmd[i])
		{
			printf("command id: %d command: %s\t in: %d  out: %d\n", tmpp->id, tmpp->cmd[i], tmpp->in, tmpp->out);
			i++;
		}
		i = 0;
		tmpp = tmpp->next;
	}
	//pars_free(*command);
} */

void	pars_free(t_pars *command)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	while (command)
	{
		tmp = command;
		command = command->next;
		while (tmp->cmd[i])
			free(tmp->cmd[i++]);
		i = 0;
		free(tmp->cmd);
		free(tmp);
	}
}

/*	Test:

	t_tok *tmp = *token;
	while (tmp)
	{
		printf("token id: %d type: %d token: %s\n", tmp->id, tmp->type, tmp->token);
		tmp = tmp->next;
	}

 */