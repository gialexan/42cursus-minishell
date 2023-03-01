/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 23:28:24 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/01 00:07:16 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_bool	is_redirect(t_token *token)
{
	if (match(type(token), TK_GREAT) ||
		match(type(token), TK_DLESS) ||
		match(type(token), TK_DGREAT) ||
		match(type(token), TK_LESS))
		return (TRUE);
	return (FALSE);
}

t_bool is_pipe(t_token *token)
{
	if (match(type(token), TK_PIPE))
		return (TRUE);
	return (FALSE);
}

t_bool is_word(t_token *token)
{
	if (match(type(token), TK_WORD))
		return (TRUE);
	return (FALSE);
}

t_bool is_eof(t_token *token)
{
	if (match(type(token), TK_EOF))
		return (TRUE);
	return (FALSE);
}

t_bool is_error(t_token *token)
{
	if (match(type(token), TK_ERROR))
		return (TRUE);
	return (FALSE);
}
