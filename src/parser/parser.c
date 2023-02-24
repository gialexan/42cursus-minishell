/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:32:19 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/24 14:56:40 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_bool word(t_token *token);
static t_bool parse(t_token *token);

t_bool syntax_analysis(t_token *token)
{
	if (token == NULL)
		return (FALSE);
	else if (marry(tk_type(token), TK_EOF))
		return (FALSE);
	else if (marry(tk_type(token), TK_PIPE))
		return (FALSE);
	else
		return(parse(token));
}

static t_bool parse(t_token *token)
{
	printf("syntax: %s\n", token->lexema);
	if (marry(tk_type(token), TK_GREAT) || 
		marry(tk_type(token), TK_DLESS) ||
		marry(tk_type(token), TK_DGREAT) ||
		marry(tk_type(token), TK_LESS))
	{
		if (marry(next_tk_type(token), TK_EOF))
			return (FALSE); //return (printf("erro 1\n"))
		return (word(next(token)));
	}
	else if (marry(tk_type(token), TK_WORD))
	{
		if (marry(next_tk_type(token), TK_EOF))
			return (TRUE); //return (printf("success 1\n"));
		return (parse(next(token)));
	}
	else if (marry(tk_type(token), TK_PIPE))
	{
		if (marry(next_tk_type(token), TK_EOF))
			return (FALSE); //return (printf("erro 3\n"))
		else if (marry(next_tk_type(token), TK_PIPE))
			return (FALSE); //return (printf("erro 4\n"));
		return (parse(next(token)));
	}
	else
		return (FALSE);
}

static t_bool word(t_token *token)
{
	if (marry(tk_type(token), TK_WORD))
	{
		printf("married: %s\n", token->lexema);
		if (marry(next_tk_type(token), TK_EOF))
			return (TRUE); //return (printf("success 2\n"));
		return (parse(next(token)));
	}
	return (FALSE); //printf("error2\n")
}
