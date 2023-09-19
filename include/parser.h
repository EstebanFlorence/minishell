/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:04:27 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/19 20:45:39 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/include/libft.h"
# include "minishell.h"
# include <stdbool.h>

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

# define STATE_NORMAL 0
# define STATE_DOUBLE_QUOTE 1
# define STATE_SINGLE_QUOTE 2
# define STATE_DOLLAR_SIGN 3
# define STATE_DOLLAR_SIGN_DOUBLE_QUOTE 4
# define STATE_REDIRECT 5

# define EMPTY 6
# define CMD 7
# define WORD 8
# define REDIRECT 9

# define OUTPUT 10
# define APPEND 11
# define INPUT 12
# define HEREDOC 13

typedef struct s_parser
{
	int				id;
	char			**cmds;

	int				in;
	int				out;

	int				numred;
	int				*redirs;
	char			**redir_name;

	bool			exec;

	struct s_parser	*next;
	struct s_parser	*prev;
}					t_pars;

typedef struct s_token
{
	int				id;
	int				type;
	char			*token;

	struct s_token	*next;
	struct s_token	*prev;
}					t_tok;

typedef struct s_exp
{
	char	**expandables;
	char	*names;
	char	*var;
	char	*expanded;
	char	*status;
}	t_exp;

#endif