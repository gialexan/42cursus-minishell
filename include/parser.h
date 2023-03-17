/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 01:25:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/17 10:38:36 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <scanner.h>

typedef struct s_cmd
{
	t_list			*token;
	struct s_cmd	*next;
}	t_cmd;

t_cmd *cmdnew();
t_cmd *addcmd(t_cmd *cmd);
t_bool is_eof(t_list *token);
t_bool is_pipe(t_list *token);
t_bool is_word(t_list *token);
t_tk_type type(t_list *token);
t_bool is_error(t_list *token);
t_list *advanced(t_list **token);
t_bool is_redirect(t_list *token);
t_cmd *syntax_analysis(t_list *token);
t_bool match(t_tk_type tk_type, t_tk_type expected);

#endif