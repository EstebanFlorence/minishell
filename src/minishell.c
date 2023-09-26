/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:44:43 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/26 15:23:05 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

void	signal_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	shell_loop(t_shell *shell)
{
	t_pars	*command;

	while (42)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		shell->exit = 0;
		shell->input = readline(shell->prompt);
		if (!ft_strncmp(shell->input, "exit", 5) || shell->input == NULL)
			shell_exit(shell);
		if (!ft_isvalid(shell->input))
		{
			add_history(shell->input);
			shell_parser(shell, &command);
			if (shell->exit == 0)
				shell_executor(&command, shell);
		}
		pars_free(command);
		free(shell->input);
	}
}

void	shell_env(char **env, t_shell *shell)
{
	int		i;
	char	**path_env;

	i = 0;
	while (env[i])
		i++;
	shell->env = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (env[++i])
		shell->env[i] = ft_strdup(env[i]);
	i = 0;
	path_env = ft_split(getenv("PATH"), ':');
	while (path_env[i])
		i++;
	shell->paths = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (path_env[++i])
		shell->paths[i] = ft_strjoin(path_env[i], "/");
	i = 0;
	while (path_env[i])
		free(path_env[i++]);
	free(path_env);
}

void	shell_innit(t_shell *shell, char **env)
{
	char	*user;

	shell->in = dup(STDIN_FILENO);
	shell->out = dup(STDOUT_FILENO);
	shell->pipe[0] = -2;
	shell->pipe[1] = -2;
	shell->status = 0;
	shell->exit = 0;
	user = ft_strjoin(PURPLE, getenv("USER"));
	shell->prompt = ft_strjoin(user, "@smolShell" CLR_RMV " > ");
	free(user);
	shell_env(env, shell);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	ft_printf("%sWelcome %s!%s\n", GREEN, getenv("USER"), CLR_RMV);
	shell_innit(&shell, env);
	shell_loop(&shell);
	return (0);
}
