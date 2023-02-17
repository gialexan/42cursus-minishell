/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:41 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/15 22:43:01 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include "../libft/libft.h"

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

typedef struct s_token
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

#endif
