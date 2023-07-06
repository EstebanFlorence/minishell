/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:44:43 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/06 02:43:40 by adi-nata         ###   ########.fr       */
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

		ft_printf("%s\n", shell->input);

		free (shell->input);
	}
}

void	shell_env(t_shell *shell)
{
	


}

void	shell_innit(t_shell *shell)
{
	char	*tmp;

	tmp = ft_strjoin(PURPLE, getenv("USER"));
	shell->prompt = ft_strjoin(tmp, "@zeshell" CLR_RMV "> ");
	free (tmp);

	//shell_env(shell);
	
}

void	shell_check()
{
	
}

int	main(int ac, char **av/* , char **env */)
{
	t_shell	shell;

	(void)ac;
	(void)av;

	ft_printf("%sWelcome %s!%s\n", GREEN, getenv("USER"), CLR_RMV);

	shell_innit(&shell);

	shell_loop(&shell);

	return (0);
}
