/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:00:04 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/01 12:36:07 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scanner.h>
#include <helper.h>

static	void	skip_space (t_scanner *scanner);
static	t_token *scan_token(t_scanner *scanner);
static	t_bool	match(t_scanner *scanner, char expected);

t_token	*lexical_analysis(t_scanner *scanner, t_token *token)
{
	if (scanner->curr > ft_strlen(scanner->cmd))
		return (token);
	scanner->start = scanner->curr;
	lstadd_back(&token, scan_token(scanner));
	return (lexical_analysis(scanner, token));
}

static t_token *scan_token(t_scanner *scanner)
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
	return (string(scanner, c));
}

static t_bool match(t_scanner *scanner, char expected)
{
	if (scanner->cmd[scanner->curr] != expected)
		return (FALSE);
	advance(scanner);
	return (TRUE);
}

static	void	skip_space (t_scanner *scanner)
{
	while (ft_isspace(scanner->cmd[scanner->curr]))
		advance (scanner);
	scanner->start = scanner->curr;
}