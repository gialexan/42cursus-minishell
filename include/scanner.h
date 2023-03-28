/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:58:35 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/27 07:58:34 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "../libft/libft.h"
# include <stdio.h>

# define METACHARS "|()<> \t\n"
# define CLOSED 0
# define UNCLOSED 1

typedef struct	s_scanner
{
	size_t			start;
	size_t			current;
	const char		*cmd;
}	t_scanner;

void		skip_space (t_scanner *scanner);
t_list		*scan_token(t_scanner *scanner);
t_scanner	init_scanner(const char *command);
t_list		*make_token(t_scanner *scanner, t_tk_type type);
t_list		*lexical_analysis(t_scanner *scanner, t_list *token);

#endif
