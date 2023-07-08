/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:45:02 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/08 18:52:21 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_wordcount(char *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && s[i] != ' ')
		{
			if (s[i + 1] == ' ' || !s[i + 1])
				words++;
			i++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	ft_printf("words: %d\n", words);
	return (words);
}

void	ft_builder(t_shell *shell)
{
	char	**words;

	words = ft_split(shell->input, ' ');

	for (int i = 0; words[i]; i++)
		ft_printf("%s\n", words[i]);

	free(words);
}

void	shell_exit(t_shell *shell)
{
	free(shell->input);
	free(shell->prompt);
	
	exit (EXIT_SUCCESS);
}

int	ft_isvalid(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < 32 && s[i] == 127)
			return (1);
		i++;
	}
	return (0);
}
