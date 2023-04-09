/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 23:28:24 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/09 15:19:42 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	is_redirect(t_list *token)
{
	if (match(token, TK_GREAT)
		|| match(token, TK_DLESS)
		|| match(token, TK_DGREAT)
		|| match(token, TK_LESS))
		return (TRUE);
	return (FALSE);
}

t_bool	is_pipe(t_list *token)
{
	if (match(token, TK_PIPE))
		return (TRUE);
	return (FALSE);
}

t_bool	is_word(t_list *token)
{
	if (match(token, TK_WORD))
		return (TRUE);
	return (FALSE);
}

t_bool	is_eof(t_list *token)
{
	if (match(token, TK_EOF))
		return (TRUE);
	return (FALSE);
}

t_bool	is_error(t_list *token)
{
	if (match(token, TK_ERROR))
		return (TRUE);
	return (FALSE);
}
