/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:00:04 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/09 15:16:25 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

static int		string(t_scanner *self, char c);
static t_list	*token_word(t_scanner *scanner, char c);
static t_bool	match(t_scanner *scanner, char expected);

t_list	*scan_token(t_scanner *scanner)
{
	char	c;

	skip_space(scanner);
	c = advance(scanner);
	if (c == '\0')
		return (make_token(scanner, TK_EOF));
	else if (c == '|')
		return (make_token(scanner, TK_PIPE));
	else if (c == '<')
	{
		if (match(scanner, '<'))
			return (make_token(scanner, TK_DLESS));
		return (make_token(scanner, TK_LESS));
	}
	else if (c == '>')
	{
		if (match(scanner, '>'))
			return (make_token(scanner, TK_DGREAT));
		return (make_token(scanner, TK_GREAT));
	}
	return (token_word(scanner, c));
}

static t_bool	match(t_scanner *scanner, char expected)
{
	if (scanner->cmd[scanner->current] != expected)
		return (FALSE);
	advance(scanner);
	return (TRUE);
}

static t_list	*token_word(t_scanner *scanner, char c)
{
	scanner->current--;
	while (!ft_strchr(METACHARS, scanner->cmd[scanner->current]))
	{
		c = advance(scanner);
		if (c == '\'' || c == '"')
		{
			if (string(scanner, c) == UNCLOSED)
				return (make_token(scanner, TK_ERROR));
			c = scanner->cmd[scanner->current];
		}
	}
	return (make_token(scanner, TK_WORD));
}

static int	string(t_scanner *self, char c)
{
	char	close;

	close = c;
	c = advance(self);
	while (c != close && c != 0)
		c = advance(self);
	if (c == 0 && c != close)
		return (UNCLOSED);
	return (CLOSED);
}
