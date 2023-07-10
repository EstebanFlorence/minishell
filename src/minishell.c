/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:44:43 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/10 17:56:07 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_shell *shell)
{
	while (42)
	{
		shell->input = readline(shell->prompt);

		if (!ft_strncmp(shell->input, "exit", 5))
			shell_exit(shell);

		if (!ft_isvalid(shell->input))
			lexer(shell);


		//printf("%s\n", shell->input);

		free(shell->input);
	}
}

void	shell_innit(t_shell *shell)
{
	char	*user;

	user = ft_strjoin(PURPLE, getenv("USER"));
	shell->prompt = ft_strjoin(user, "@zeShell" CLR_RMV " > ");
	free (user);

	shell->exit = 0;
	shell->words = 0;

	//shell_env(shell);

}

int	main(int ac, char **av/* , char **env */)
{
	t_shell	shell;
//	t_lexer	*lexer;

	(void)ac;
	(void)av;
//	lexer = NULL;

	ft_printf("%sWelcome %s!%s\n", GREEN, getenv("USER"), CLR_RMV);

	shell_innit(&shell);

	shell_loop(&shell);

	return (0);
}
