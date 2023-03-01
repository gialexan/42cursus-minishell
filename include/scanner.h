/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:58:35 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/01 12:39:44 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "../libft/libft.h"
# include <stdio.h>

# define METACHARS "|()<> \t\n"

typedef enum s_tk_type
{
	TK_EOF,
	TK_WORD,
	TK_PIPE,
	TK_LESS,
	TK_GREAT,
	TK_DLESS,
	TK_ERROR,
	TK_DGREAT,
}	t_tk_type;

typedef struct s_token //desalocar a linkedlist
{
	t_tk_type		tk_type;
	const char		*lexema; //campo lexema foi malocado.
	struct s_token	*next;
}	t_token;

typedef struct	s_scanner
{
	size_t			curr;
	size_t			start;
	const char		*cmd;
}	t_scanner;

char		advance(t_scanner *scanner);
t_scanner	init_scanner(const char *command);
t_token		*string(t_scanner *scanner, char c);
t_token		*make_token(t_scanner *scanner, t_tk_type type);
t_token		*lexical_analysis(t_scanner *scanner, t_token *token);

#endif
