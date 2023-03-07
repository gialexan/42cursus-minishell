/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:00:04 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/07 20:20:39 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scanner.h>

static char		advance(t_scanner *scanner);
static t_token *word(t_scanner *scanner, char c);
static t_token *string(t_scanner *scanner, char c);
static t_token *word_quote(t_scanner *scanner, char c);
static t_bool	match(t_scanner *scanner, char expected);

t_token *scan_token(t_scanner *scanner)
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
	else
	{
		if (ft_isquote(c))
			return (word_quote(scanner, c));
		return (word(scanner, c));
	}
}

static char	advance(t_scanner *scanner)
{
	scanner->curr++;
	return (scanner->cmd[scanner->curr - 1]);
}

static t_bool match(t_scanner *scanner, char expected)
{
	if (scanner->cmd[scanner->curr] != expected)
		return (FALSE);
	advance(scanner);
	return (TRUE);
}

static	t_token *word(t_scanner *scanner, char c)
{
	c = scanner->cmd[--scanner->curr];
	while (!ft_strchr(METACHARS, c))
	c = scanner->cmd[++scanner->curr];
	return (make_token(scanner, TK_WORD));
}

static	t_token *word_quote(t_scanner *scanner, char c)
{
	char close;

	close = c;
	c = advance(scanner);
	while (c != 0 && c != close)
	c = advance(scanner);
	if (c == 0 && c != close)
		return (make_token(scanner, TK_ERROR));
	return (make_token(scanner, TK_WORD));
}
