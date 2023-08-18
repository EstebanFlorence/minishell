/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:45:02 by adi-nata          #+#    #+#             */
/*   Updated: 2023/08/18 00:02:47 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_bzero(void *s, unsigned int start, int end)
{
	int	i;

	i = start;
	while (i < end)
		((unsigned char *)s)[i++] = '\0';
}

int	strchr_index(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_error(int n)
{
	write(STDERR_FILENO, "Error:\n", 8);
	if (n == 0)
		write(STDERR_FILENO, "> Invalid input\n", 17);
	
}

int	check_builtins(char *s)
{
	if (!ft_strncmp(s, "echo", 5))
		return (0);

	else if (!ft_strncmp(s, "cd", 3))
		return (0);

	else if (!ft_strncmp(s, "pwd", 4))
		return (0);

	else if (!ft_strncmp(s, "export", 7))
		return (0);

	else if (!ft_strncmp(s, "unset", 6))
		return (0);

	else if (!ft_strncmp(s, "env", 4))
		return (0);

	//else if (!ft_strncmp(s, "exit", 3))
		//shell_exit()

	return (1);
}

void	shell_exit(t_shell *shell)
{
	int	i;

	rl_clear_history();
	free(shell->input);
	free(shell->prompt);
	i = 0;
	while (shell->env[i])
		free(shell->env[i++]);
	free(shell->env);
	i = 0;
	while (shell->paths[i])
		free(shell->paths[i++]);
	free(shell->paths);

	exit (EXIT_SUCCESS);
}

int	ft_isvalid(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) < 1 || ft_strlen(s) > INPUT_SIZE)
		return (0);
	while (s[i])
	{
		if (s[i] < 32 && s[i] == 127)
			return (1);
		i++;
	}
	return (0);
}
