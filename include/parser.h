/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 01:25:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/24 14:56:18 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scanner.h"
# include <stdio.h>

t_token *next(t_token *token);
t_tk_type tk_type(t_token *token);
t_bool syntax_analysis(t_token *token);
t_tk_type next_tk_type(t_token *token);
t_bool marry(t_tk_type tk_type, t_tk_type expected);

#endif