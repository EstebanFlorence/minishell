/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:44:45 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/13 02:48:16 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"

# include <stdbool.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>

# define HEREDOC	"./.heredoc"

# define CLR_RMV	"\033[0m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define PURPLE		"\033[1;35m"
# define CYAN		"\033[1;36m"

typedef struct	s_parser
{
	int				id;
	char			*token;

	int				redirect;
	int				pipe;
	int				expand;

	struct s_parser	*next;
	struct s_parser	*prev;
}	t_pars;

typedef struct	s_lexer
{
	int				id;
	char			*token;

	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lex;

typedef struct	s_shell
{
	char	*prompt;
	char	*input;
	char	**inputs;
	char	**env;
	char	**path;

	int		words;

	int		exit;

	pid_t	pid;

	bool	history;

}	t_shell;


void		shell_innit(t_shell *shell);
void		shell_env(t_shell *shell);
void		shell_loop(t_shell *shell);
void		shell_exit(t_shell *shell);

//	Tools
void		ft_error(int n);
int			ft_isvalid(char *s);
int			check_builtins(char *s);

//	Lexer
void		ft_lex(t_shell *shell, t_lex **lexer);
void		lex_innit(t_shell *shell, t_lex **lexer);
void		lex_lstadd_back(t_lex **lexer, t_lex *new);
void		lex_remove(t_lex *end, t_lex *start);
void		lex_free(t_lex *lexer);
int			lex_wordscount(char *s);
t_lex		*lex_lstlast(t_lex *lexer);
t_lex		*lex_lstnew(int i, char *s);

//	Parser
void		ft_pars(t_shell *shell);
void		pars_piper(t_lex **lexer, t_pars **parser);
void		pars_lstadd(t_pars **parser, char *s);
void		pars_lstadd_back(t_pars **parser, t_pars *new);
void		pars_commander(t_lex *start, t_lex *end, t_pars **parser);
void		pars_free(t_pars *parser);
int			pars_finder(t_lex *lexer);
t_lex		*pars_starter(t_lex *lexer);
t_pars		*pars_lstlast(t_pars *parser);
t_pars		*pars_lstnew(char *s, int id);



#endif