/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:04:27 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/16 18:17:16 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# include <stdbool.h>

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

# define STATE_NORMAL 0
# define STATE_DOUBLE_QUOTE 1
# define STATE_SINGLE_QUOTE 2
# define STATE_DOLLAR_SIGN 3
# define STATE_DOLLAR_SIGN_DOUBLE_QUOTE 4

# define EMPTY		0
# define CMD		1
# define ARG		2
# define TRUNC		3
# define APPEND		4
# define INPUT		5
# define HEREDOC	6
# define PIPE		7
# define EXPAND		8

typedef struct	s_parser
{
	int				id;
	char			*token;

	int				in;
	int				out;

	struct s_parser	*next;
	struct s_parser	*prev;
}	t_pars;

typedef struct	s_token
{
	int				id;
	int				type;
	char			*token;

	struct s_token	*next;
	struct s_token	*prev;
}	t_tok;

typedef struct	s_lexer
{
	int		state;
	int		len;
	bool	in_quotes;
	char	*word;

}	t_lex;


#endif