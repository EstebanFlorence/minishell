/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:04:27 by adi-nata          #+#    #+#             */
/*   Updated: 2023/09/01 23:08:52 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "../libft/include/libft.h"

# include <stdbool.h>

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

# define STATE_NORMAL 0
# define STATE_DOUBLE_QUOTE 1
# define STATE_SINGLE_QUOTE 2
# define STATE_DOLLAR_SIGN 3
# define STATE_DOLLAR_SIGN_DOUBLE_QUOTE 4
# define STATE_REDIRECT 5

# define EMPTY		6
# define CMD		7
# define ARG		8
# define REDIRECT	9

typedef struct	s_parser
{
	int				id;
	char			**cmd;

	int				in;
	int				out;

	int				status;

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


#endif