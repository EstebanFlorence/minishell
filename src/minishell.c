/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:44:43 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/06 00:54:15 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_shell *shell)
{
	while (42)
	{
		shell->input = readline(shell->prompt);

		ft_printf("%s\n", shell->input);

		free (shell->input);
	}
}

void	shell_innit(t_shell *shell)
{
	char	*tmp;

	tmp = ft_strjoin(PURPLE, getenv("USER"));
	shell->prompt = ft_strjoin(tmp, "@zeshell\033[0m > ");

	free (tmp);
	
}

void	shell_check()
{
	
}

int	main(int ac, char **av/* , char **env */)
{
	t_shell	shell;

/* 	t_shell	*shell;

	shell_check();
	
	shell_innit();

	shell_loop();

	shell_close(); */

	(void)ac;
	(void)av;

	ft_printf("Welcome %s!\n", getenv("USER"));

	shell_innit(&shell);

	shell_loop(&shell);

	return (0);
}
