/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:44:45 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/01 19:38:13 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"

# include <stdbool.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define INPUT_SIZE 4095

# define HEREPATH	"./.heredoc"
# define FILESPATH	"./.files/"

# define CLR_RMV	"\033[0m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define PURPLE		"\033[1;35m"
# define CYAN		"\033[1;36m"

typedef struct	s_shell
{
	char	*prompt;
	char	*input;

	char	**env;
	char	**paths;

	int		pipe[2];
	int		in;
	int		out;
	int		status;

	pid_t	pid;

	int		exit;
	bool	history;

}	t_shell;

typedef struct	s_lexer
{
	int		state;
	int		type;
	int		start;
	size_t	len;
	char	buffer[INPUT_SIZE];

	t_shell	*shell;

}	t_lex;

void		shell_innit(t_shell *shell, char **env);
void		shell_env(char **env, t_shell *shell);
void		shell_loop(t_shell *shell);
void		shell_free(t_shell *shell);
void		shell_exit(t_shell *shell);
void		shell_command(t_shell *shell, t_pars **command);
void		shell_parser(t_shell *shell, t_pars **command);

//	Test
void		shell_executor(t_pars **command, t_shell *shell);
void		execute(t_pars *command, t_shell *shell);


//	Tools
void		ft_error(int n);
int			ft_isvalid(char *s);
int			check_builtins(char *s);
int			strchr_index(char *s, char c);

char		**pipe_split(const char *s, char pipe);
void		pipe_splitta(const char *s, char pipe, char **split, size_t n);
size_t		pipe_numstr(const char *s, char pipe);

void		signal_handler(int sig);
void		signal_print(int sig);


//	Lexer
void		lex_tokenizer(t_shell *shell, char *input, t_tok **token, int *id);
void		lex_free_inputs(char **inputs);
void		lex_bzero(void *s, unsigned int start, int end);
int			lex_type(const char *s, t_shell *shell);
int			is_command(const char *cmd, t_shell *shell);

void		state_normal(char c, t_lex *lex, t_tok **token, int *id);
void		state_normal_space(t_lex *lex, t_tok **token, int *id);
void		state_normal_dquote(t_lex *lex);
void		state_normal_squote(t_lex *lex);
void		state_normal_dollar(t_lex *lex);
void		state_quotes(char c, t_lex *lex);
void		state_quotes_double(char c, t_lex *lex);
void		state_quotes_single(char c, t_lex *lex);
void		state_dollar(char c, t_lex *lex, t_tok **token, int *id);
void		state_dollarquotes(char c, t_lex *lex, t_tok **token, int *id);

void		lex_expand(t_lex *lexer);
void		lex_multiexpand(t_lex *lexer);
char		*lex_expand_status(char *s, t_lex *lexer);
int			is_status(char *s);

void		tok_lstadd(t_tok **token, t_lex *lexer, int *id);
void		tok_lstadd_back(t_tok **token, t_tok *new);
t_tok		*tok_lstlast(t_tok *token);
t_tok		*tok_lstnew(t_lex *lexer, int *id);

void		lex_remove(t_tok *end, t_tok *start);
void		tok_free(t_tok *token);

//	Parser
void		pars_commander(t_tok *token, t_pars *command);
void		pars_free(t_pars *command);

void		pars_redirect(t_tok *token, t_pars *command);
int	 		here_doc(t_tok *token);


void		pars_lstadd(t_pars **command, int id);
void		pars_lstadd_back(t_pars **command, t_pars *new);
t_pars		*pars_lstlast(t_pars *command);
t_pars		*pars_lstnew(int id);

//	Environment
void		env_freepaths(char **paths);


//	Executer
void		ft_exec(t_shell *shell, t_pars *command, char **env);
int			exec_check(t_shell *shell, t_pars **command, char **env);
char		*exec_path(char *cmd, char **env);

#endif