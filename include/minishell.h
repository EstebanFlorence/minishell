/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:44:45 by adi-nata          #+#    #+#             */
/*   Updated: 2023/10/02 16:30:52 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/ft_printf.h"
# include "../libft/include/libft.h"
# include "parser.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/wait.h>

# define INPUT_SIZE 4095

# define HEREPATH "./.heredoc"
# define FILESPATH "./.files/"

# define CLR_RMV "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"

extern int	g_exit;

typedef struct s_shell
{
	char	*prompt;
	char	*input;

	char	**env;
	char	**paths;
	char	**export;

	int		pipe[2];
	int		in;
	int		out;
	int		status;

	pid_t	pid;

	int		exit;
	bool	history;

}			t_shell;

typedef struct s_lexer
{
	int		state;
	int		type;
	int		start;
	size_t	len;
	char	buffer[INPUT_SIZE];

	t_shell	*shell;

}			t_lex;

void		shell_innit(t_shell *shell, char **env);
void		shell_env(char **env, t_shell *shell);
void		shell_loop(t_shell *shell);
void		shell_free(t_shell *shell);
void		shell_freepath(t_shell *shell);
void		shell_exit(t_shell *shell);
void		shell_parser(t_shell *shell, t_pars **command);
char		*shell_getenv(char *var, t_shell *shell);

//	Exec
void		shell_executor(t_pars **command, t_shell *shell);
void		execvshell(t_pars *command, t_shell *shell);
void		exec1(t_pars *command, t_shell *shell);
void		exec2(char *cmd_path, t_pars *tmp, t_pars *command, t_shell *shell);
void		fork_command(t_pars *cmd, t_shell *shell);
void		child_process(t_pars *cmd, t_shell *shell);
void		parent_process(t_pars *cmd, t_shell *shell);
void		parent_end(t_shell *shell);
void		exec_redir(t_pars *cmd, t_shell *shell);
void		close_redir(t_pars *cmd);
void		exec_builtin_main(t_pars *cmd, t_shell *shell);
void		exec_builtin_fork(t_pars *cmd, t_shell *shell);
void		handle_redir(t_pars *cmd);
void		handle_piperedir(t_pars *cmd, t_shell *shell);

//	Tools
void		ft_error(int n);
void		command_notfound(t_pars *cmd);
int			ft_isvalid(char *s);
int			strchr_index(char *s, char c);
void		set_path(char *path, t_shell *shell);

char		**pipe_split(const char *s, char pipe);
void		pipe_splitter(const char *s, char pipe, char **split, size_t n);
char		*pipe_splitter_add(const char *s, size_t *i, size_t *len);
void		pipe_splitter_quotes(const char *s, size_t *i, size_t *len);

int			pipe_numstr(const char *s, char pipe);
void		pipe_numstr_add(size_t *n, size_t *len);
int			pipe_numstr_quote(const char *s, size_t *i);

void		signal_handler(int sig);
void		signal_print(int sig);

//	Lexer
void		lex_tokenizer(t_shell *shell, char *input, t_tok **token, int *id);
void		lex_tokenizer_end(t_lex *lex, t_tok **token, int *id);
void		lex_free_inputs(char **inputs);
void		lex_bzero(void *s, unsigned int start, int end);
int			lex_type(const char *s);
int			is_command(const char *cmd, t_shell *shell);

void		state_normal(char c, t_lex *lex, t_tok **token, int *id);
void		state_normal_space(t_lex *lex, t_tok **token, int *id);
void		state_normal_dollar(t_lex *lex);
void		state_quotes(char c, t_lex *lex);
void		state_quotes_double(char c, t_lex *lex);
void		state_quotes_single(char c, t_lex *lex);
void		state_dollar(char c, t_lex *lex, t_tok **token, int *id);
void		state_dollar_end(t_lex *lex, t_tok **token, int *id);
void		state_dollarquotes(char c, t_lex *lex, t_tok **token, int *id);
void		state_dollarquote_append(char c, t_lex *lex);
void		state_dollarquote_end(t_lex *lex, t_tok **token, int *id);
void		state_dollar_exp(char c, t_lex *lex);
void		state_dollar_append(char c, t_lex *lex);
void		state_redirect(char c, t_lex *lex, t_tok **token, int *id);

void		lex_expand(t_lex *lexer, t_shell *shell);
void		lex_expand_status(char *name, t_lex *lexer);
void		lex_expand_var(char *name, t_lex *lexer, t_shell *shell);
void		lex_multiexpand(t_lex *lexer, t_shell *shell);
void		lex_multiexpand_status(int i, t_exp *exp);
void		lex_multiexpand_var(t_exp *exp);
void		lex_multiexpand_putvar(t_exp *exp, t_lex *lexer);
void		lex_expand_free(t_exp *exp);

int			is_status(char *s);
char		*exp_status(char *var);
void		status_putstat(char *status, char *exp, int *i);
void		status_putvar(char *var, char *exp, int *i, int *j);

void		tok_lstadd(t_tok **token, t_lex *lexer, int *id);
void		tok_lstadd_back(t_tok **token, t_tok *new);
t_tok		*tok_lstlast(t_tok *token);
t_tok		*tok_lstnew(t_lex *lexer, int *id);

void		lex_remove(t_tok *end, t_tok *start);
void		tok_free(t_tok *token);

void		lex_append(char c, t_lex *lex);

//	Parser
char		**input_split(t_shell *shell);
void		pars_loop(char **inputs, t_tok *token,
				t_pars **command, t_shell *shell);
void		pars_commander(t_tok *token, t_pars *command);
void		commander_alloc(t_tok *token, t_pars *command);
void		commander_loop(t_tok *token, t_pars *command);
void		pars_free(t_pars *command);
void		pars_free_content(t_pars **command);

void		pars_lstadd(t_pars **command, int id);
void		pars_lstadd_back(t_pars **command, t_pars *new);
t_pars		*pars_lstlast(t_pars *command);
t_pars		*pars_lstnew(int id);

//	Redirect
void		pars_redir(t_tok *token, int r, t_pars *command);
void		redir_output(int i, t_pars *cmd, t_shell *shell);
void		redir_append(int i, t_pars *cmd, t_shell *shell);
void		redir_input(int i, t_pars *cmd, t_shell *shell);
void		redir_heredoc(int i, t_pars *cmd, t_shell *shell);
int			here_doc(int i, t_pars *cmd, t_shell *shell);

//	Builtin
int			is_builtin(char *cmd);
int			exec_builtin(t_pars *cmd, t_shell *shell);
int			ft_cd(char **str, t_shell *shell);
int			ft_stupid_norm(char *pwd, char *oldpwd);
int			ft_echo(char **str);
int			ft_env(t_shell *shell);
int			ft_export(char **str, t_shell *shell);
int			ft_unset(char **str, t_shell *shell);
int			ft_setexport(char *name, char *value, t_shell *shell);
int			ft_setexport_addenv(char *name, char *value, t_shell *shell);
int			ft_unsetenv(char *name, t_shell *shell);
int			ft_unsetexp(char *name, t_shell *shell);
int			ft_setenv(char *name, char *value, t_shell *shell);
int			ft_exit(char **str, t_shell *shell, t_pars *cmd);
int			ft_pwd(int n);
char		*varalloc(char **str);
char		**ft_realloc(char **env, size_t size);

#endif
