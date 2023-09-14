/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:21:54 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/14 22:11:05 by adi-nata         ###   ########.fr       */
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
	printf("Command not found: %s\n", tmp->cmds[0]);
	//write(STDERR_FILENO, "Command not found: &s\n", 23);
	pars_free(command);
	shell_free(shell);
	exit(127);
}

void	close_redir(t_pars *cmd)
{
	if (cmd->in)
		close(cmd->in);
	if (cmd->out)
		close(cmd->out);
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
				exit_status = 1;
				shell->exit = exit_status;
			}
		}
		if (cmd->redirs[i] == APPEND)
		{
			if (cmd->out != -2)
				close(cmd->out);
			cmd->out = open(cmd->redir_name[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
			if (cmd->out < 0)
			{
				perror(cmd->redir_name[i]);
				exit_status = 1;
				shell->exit = exit_status;
			}
		}
		if (cmd->redirs[i] == INPUT)
		{
			if (cmd->in != -2)
				close(cmd->in);
			cmd->in = open(cmd->redir_name[i], O_RDONLY);
			if (cmd->in < 0)
			{
				perror(cmd->redir_name[i]);
				exit_status = 1;
				shell->exit = exit_status;
			}
		}
		if (cmd->redirs[i] == HEREDOC)
		{
			if (cmd->in != -2)
				close(cmd->in);
			//cmd->in = here_doc();
			if (cmd->in < 0)
			{
				perror(cmd->redir_name[i]);
				exit_status = 1;
				shell->exit = exit_status;
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

	if (cmd->out != -2)
	{
		close(cmd->out);
	}
	if (cmd->in != -2)
	{
		close(cmd->in);
	}
	else if (cmd->next)
	{
		close(shell->pipe[1]);
		dup2(shell->pipe[0], STDIN_FILENO);
		close(shell->pipe[0]);
	}
	
	if (cmd->out != -2)
		close(cmd->out);	


	waitpid(shell->pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		shell->exit = exit_status;
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
	if (cmd->in != -2)
	{
		//close(shell->pipe[1]);
		close(shell->pipe[0]);
		close(STDIN_FILENO);
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != -2)
	{
		//close(shell->pipe[0]);
		close(shell->pipe[1]);
		close(STDOUT_FILENO);
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	else if (cmd->next)
	{
		if (cmd->in == -2)
			close(shell->pipe[0]);
		dup2(shell->pipe[1], STDOUT_FILENO);
		close(shell->pipe[1]);
	}
	if (is_builtin(cmd->cmds[0]))
	{
		exit_status = exec_builtin(cmd, shell);
		shell->exit = exit_status;
		pars_free(cmd);
		shell_free(shell);
		exit(exit_status);
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
		if (cmd->in == -1 || cmd->out == -1)
		{
			//cmd = cmd->next;
			//continue ;
			break ;
		}
		if (cmd->next)
		{
			if (pipe(shell->pipe) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			//close(shell->pipe[0]);
			//close(shell->pipe[1]);
		}

		if (cmd->exec == false)
		{
			if (cmd->numred)
				exec_redir(cmd, shell);
			close_redir(cmd);
		}
		else
		{
			if (is_builtin(cmd->cmds[0]) && ft_strncmp(cmd->cmds[0], "echo", 5) && ft_strncmp(cmd->cmds[0], "pwd", 4))
			{
				if (cmd->numred)
				{
					exec_redir(cmd, shell);
				}
				exec_builtin(cmd, shell);
			}
			else
				exec_command(cmd, shell);
		}
		cmd = cmd->next;
	}
	dup2(shell->in, STDIN_FILENO);
	dup2(shell->out, STDOUT_FILENO);
}
