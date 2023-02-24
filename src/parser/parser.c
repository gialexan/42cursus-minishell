/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:32:19 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/24 21:08:43 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_bool words(t_token *token);
static t_bool pipes(t_token *token);
static t_bool parser(t_token *token);

t_bool syntax_error(t_token *token)
{
	dprintf(STDERR_FILENO, "minihell: ");
	if (marry(tk_type(token), TK_ERROR))
		dprintf(STDERR_FILENO, "error unclosed quotes %s\n", token->lexema);
	else
	{
		dprintf(STDERR_FILENO, "syntax error near unexpected token ");
		if (marry(tk_type(token), TK_EOF))
			dprintf(STDERR_FILENO, "'newline'\n");
		else
			dprintf(STDERR_FILENO, "'%s'\n", token->lexema);
	}
	return (FALSE);
}

t_bool syntax_analysis(t_token *token)
{
	if (token == NULL)
		return (FALSE);
	else if (marry(tk_type(token), TK_EOF))
		return (FALSE);
	else if (marry(tk_type(token), TK_PIPE))
		return (syntax_error(token)); //OK
	else
		return (parser(token));
}

static t_bool parser(t_token *token)
{
	//printf("syntax: %s\n", token->lexema);
	if (marry(tk_type(token), TK_GREAT) ||
		marry(tk_type(token), TK_DLESS) ||
		marry(tk_type(token), TK_DGREAT) ||
		marry(tk_type(token), TK_LESS))
		return (words(next(token)));
	else if (marry(tk_type(token), TK_WORD))
		return (parser(next(token)));
	else if (marry(tk_type(token), TK_PIPE))
		return (pipes(token));
	else if (marry(tk_type(token), TK_EOF))
		return (TRUE);
	return (syntax_error(token));
}

static	t_bool pipes(t_token *token)
{
	if (marry(next_tk_type(token), TK_EOF))
		return (syntax_error(token)); //OK
	else if (marry(next_tk_type(token), TK_PIPE))
		return (syntax_error(token)); //OK
	return (parser(next(token)));
}

static	t_bool words(t_token *token)
{
	if (marry(tk_type(token), TK_WORD)) //printf("married: %s\n", token->lexema);
		return (parser(next(token)));
	return (syntax_error(token)); //OK
}
