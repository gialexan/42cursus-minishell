/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:58:35 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 14:49:50 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "../libft/libft.h"
# include <stdio.h>

# define METACHARS "|()<> \t\n"

typedef struct	s_scanner
{
	size_t			curr;
	size_t			start;
	const char		*cmd;
}	t_scanner;

void		skip_space (t_scanner *scanner);
t_list		*scan_token(t_scanner *scanner);
t_scanner	init_scanner(const char *command);
t_list		*make_token(t_scanner *scanner, t_tk_type type);
t_list		*lexical_analysis(t_scanner *scanner, t_list *token);

#endif
