/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:32:17 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/24 14:51:06 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token *next(t_token *token)
{
	return (token->next);
}

t_tk_type tk_type(t_token *token)
{
	return (token->tk_type);
}

t_tk_type next_tk_type(t_token *token)
{
	return (token->next->tk_type);
}

t_bool marry(t_tk_type tk_type, t_tk_type expected)
{
	return (tk_type == expected);
}
