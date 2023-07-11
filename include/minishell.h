/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:44:45 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/11 20:44:00 by adi-nata         ###   ########.fr       */
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
}	t_parser;

typedef struct	s_lexer
{
	int				id;
	char			*token;

	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

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
void		ft_lexer(t_shell *shell, t_lexer **lexer);
void		lex_innit(t_shell *shell, t_lexer **lexer);
void		lex_lstadd_back(t_lexer **lexer, t_lexer *new);
void		lex_free(t_lexer *lexer);
int			lex_wordscount(char *s);
t_lexer		*lex_lstlast(t_lexer *lexer);
t_lexer		*lex_lstnew(int i, char *s);

//	Parser
void		ft_parser(t_shell *shell);
void		pars_checker(t_lexer **lexer, t_parser **parser);
void		pars_lstadd(t_parser **parser, char *s);
void		pars_lstadd_back(t_parser **parser, t_parser *new);
void		pars_commander(t_lexer *lexer, t_parser **parser);
void		pars_free(t_parser *parser);
int			pars_finder(t_lexer *lexer);
t_lexer		*pars_starter(t_lexer *lexer);
t_parser	*pars_lstlast(t_parser *parser);
t_parser	*pars_lstnew(char *s, int id);



#endif