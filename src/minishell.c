/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:44:43 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/17 18:02:36 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_shell *shell, char **env)
{
	t_pars	*parser;

	parser = NULL;
	(void)env;
	while (42)
	{
		shell->input = readline(shell->prompt);

		if (!ft_strncmp(shell->input, "exit", 5))
			shell_exit(shell);

		if (!ft_isvalid(shell->input))
		{
			//shell_parser(shell, &parser);
			//ft_exec(shell, &parser, env);
		}

		free(shell->input);
	}
}

void	shell_innit(t_shell *shell)
{
	char	*user;

	shell->in = dup(STDIN_FILENO);
	shell->out = dup(STDOUT_FILENO);

	user = ft_strjoin(PURPLE, getenv("USER"));
	shell->prompt = ft_strjoin(user, "@zeShell" CLR_RMV " > ");
	free (user);

	//shell_env(env, &shell);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	(void)env;

	ft_printf("%sWelcome %s!%s\n", GREEN, getenv("USER"), CLR_RMV);

	shell_innit(&shell);

	shell_loop(&shell, env);

	return (0);
}
