/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:21:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/18 18:13:13 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_print(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	exec2(char *cmd_path, t_pars *tmp, t_pars *command, t_shell *shell)
{
	if (command->cmds[0] == NULL)
		return ;
	if (access(cmd_path, F_OK) == 0)
	{
		execve(cmd_path, tmp->cmds, shell->env);
		perror("execve2");
		pars_free(command);
		shell_free(shell);
		exit(126);
	}
}

void	exec1(t_pars *command, t_shell *shell)
{
	if (command->cmds[0] == NULL)
		return ;
	if (access(command->cmds[0], F_OK) == 0)
	{
		execve(command->cmds[0], command->cmds, shell->env);
		perror("execve1");
		pars_free(command);
		shell_free(shell);
		exit(126);
	}
}

void	execute(t_pars *command, t_shell *shell)
{
	int		i;
	int		j;
	char	*cmd_path;
	t_pars	*tmp;

	i = 0;
	j = 0;
	exec1(command, shell);
	tmp = command;
	while (tmp->cmds[i])
	{
		while (shell->paths[j])
		{
			cmd_path = ft_strjoin(shell->paths[j], tmp->cmds[i]);
			exec2(cmd_path, tmp, command, shell);
			free(cmd_path);
			j++;
		}
		j = 0;
		i++;
	}
	write(STDERR_FILENO, "Command not found: ", 20);
	if (tmp->cmds[0])
		write(STDERR_FILENO, tmp->cmds[0], ft_strlen(tmp->cmds[0]));
	else
		write(STDERR_FILENO, "\'\'", 3);
	write(STDERR_FILENO, "\n", 2);
	pars_free(command);
	shell_free(shell);
	exit(127);
}

void	close_pipe(t_pars *cmd, t_shell *shell)
{
	if (cmd->next)
	{
		if (cmd->in == -2)
		{
			close(shell->pipe[0]);
		}
		if (cmd->out == -2)
		{
			close(shell->pipe[1]);
		}
	}
}

void	close_redir(t_pars *cmd)
{
	if (cmd->in != -2)
		close(cmd->in);
	if (cmd->out != -2)
		close(cmd->out);
}

void	handle_redir(t_pars *cmd)
{
	if (cmd->in != -2)
	{
		close(STDIN_FILENO);
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != -2)
	{
		close(STDOUT_FILENO);
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
}

void	exec_redir(t_pars *cmd, t_shell *shell)
{
	int	i;
	int	n;

	i = 0;
	n = cmd->numred;
	while (i < n)
	{
		if (cmd->redirs[i] == OUTPUT)
		{
			if (cmd->out != -2)
				close(cmd->out);
			cmd->out = open(cmd->redir_name[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (cmd->out < 0)
			{
				perror(cmd->redir_name[i]);
				g_exit = 1;
				shell->exit = g_exit;
			}
		}
		else if (cmd->redirs[i] == APPEND)
		{
			if (cmd->out != -2)
				close(cmd->out);
			cmd->out = open(cmd->redir_name[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
			if (cmd->out < 0)
			{
				perror(cmd->redir_name[i]);
				g_exit = 1;
				shell->exit = g_exit;
			}
		}
		else if (cmd->redirs[i] == INPUT)
		{
			if (cmd->in != -2)
				close(cmd->in);
			cmd->in = open(cmd->redir_name[i], O_RDONLY);
			if (cmd->in < 0)
			{
				perror(cmd->redir_name[i]);
				g_exit = 1;
				shell->exit = g_exit;
			}
		}
		else if (cmd->redirs[i] == HEREDOC)
		{
			if (cmd->in != -2)
				close(cmd->in);
			//cmd->in = here_doc();
			if (cmd->in < 0)
			{
				perror(cmd->redir_name[i]);
				g_exit = 1;
				shell->exit = g_exit;
			}
		}
		i++;
	}
}

void	parent_process(t_pars *cmd, t_shell *shell)
{
	int	status;

	signal(SIGINT, signal_print);
	signal(SIGQUIT, signal_print);

	if (cmd->exec == false)
	{
		if (cmd->next)
			close(shell->pipe[1]);
	}
	else if (cmd->next)
	{
		close(shell->pipe[1]);
		if (cmd->cmds[0])
		{
			dup2(shell->pipe[0], STDIN_FILENO);
			close(shell->pipe[0]);
		}
	}
	if (cmd->out != -2)
	{
		close(cmd->out);
	}
	if (cmd->in != -2)
	{
		close(cmd->in);
	}
	waitpid(shell->pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit = WEXITSTATUS(status);
		shell->exit = g_exit;
	}
	else if (WIFSIGNALED(status))
	{
		g_exit = WTERMSIG(status) + 128;
		shell->exit = g_exit;
	}
}

void	child_process(t_pars *cmd, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->numred)
	{
		exec_redir(cmd, shell);
	}
	if (cmd->exec == false)
	{
		close_redir(cmd);
		if (cmd->next)
			close(shell->pipe[0]);
		pars_free(cmd);
		shell_exit(shell);
	}
	else if (cmd->next)
	{
		close(shell->pipe[0]);
		if (cmd->in != -2)
		{
			dup2(cmd->in, STDIN_FILENO);
			close(cmd->in);
		}
		if (cmd->out != -2)
		{
			dup2(cmd->out, STDOUT_FILENO);
			close(cmd->out);
		}
		else
		{
			dup2(shell->pipe[1], STDOUT_FILENO);
			close(shell->pipe[1]);
		}
	}
	else
	{
		handle_redir(cmd);
	}
	if (is_builtin(cmd->cmds[0]))
	{
		g_exit = exec_builtin(cmd, shell);
		shell->exit = g_exit;
		pars_free(cmd);
		shell_free(shell);
		exit(g_exit);
	}
	else if (cmd->exec == true)
		execute(cmd, shell);
}

void	exec_command(t_pars *cmd, t_shell *shell)
{
	shell->pid = fork();
	if (shell->pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (shell->pid == 0)
	{
		child_process(cmd, shell);
	}
	else
	{
		parent_process(cmd, shell);
	}
}

void	shell_executor(t_pars **command, t_shell *shell)
{
	t_pars	*cmd;

	cmd = *command;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(shell->pipe) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		if (!cmd->next && is_builtin(cmd->cmds[0]) == 2)
		{
			if (cmd->numred)
			{
				exec_redir(cmd, shell);
				handle_redir(cmd);
			}
			exec_builtin(cmd, shell);
			if (cmd->out != -2)
			{
				close(cmd->out);
			}
			if (cmd->in != -2)
			{
				close(cmd->in);
			}
			//dup2(shell->in, STDIN_FILENO);
			//dup2(shell->out, STDOUT_FILENO);
		}
		else
			exec_command(cmd, shell);
		cmd = cmd->next;
	}
	dup2(shell->in, STDIN_FILENO);
	dup2(shell->out, STDOUT_FILENO);
}
