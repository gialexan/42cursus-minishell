/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 01:25:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/28 22:05:13 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <scanner.h>
# include <exec.h>
# include <helper.h>

t_tk_type type(t_token *token);
t_cmd *syntax_analysis(t_token *token);
t_bool match(t_tk_type tk_type, t_tk_type expected);

#endif