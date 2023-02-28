/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:00:02 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/28 12:38:19 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scanner.h>

void	skip_space (t_scanner *scanner)
{
	while (ft_isspace(scanner->cmd[scanner->curr]))
		advance (scanner);
	scanner->start = scanner->curr;
}

char	advance(t_scanner *scanner)
{
	scanner->curr++;
	return (scanner->cmd[scanner->curr - 1]);
}

t_scanner	init_scanner(const char *command)
{
	t_scanner scanner;

	scanner.curr = 0;
	scanner.cmd = command;
	return (scanner);
}

t_token *make_token(t_scanner *scanner, t_tk_type type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->lexema = ft_substr(scanner->cmd, scanner->start,
			scanner->curr - scanner->start);
	token->tk_type = type;
	token->next = NULL;
	return (token);
}

t_token *string(t_scanner *scanner, char c)
{
	char close;

	if (ft_isquote(c))
	{
		close = c;
		c = advance(scanner);
		while (c != 0 && c != close)
		c = advance(scanner);
		if (c == 0 && c != close)
			return (make_token(scanner, TK_ERROR));
		return (make_token(scanner, TK_WORD));
	}
	else
	{
		c = scanner->cmd[--scanner->curr];
		while (!ft_strchr(METACHARS, c))
		c = scanner->cmd[++scanner->curr];
		return (make_token(scanner, TK_WORD));
	}
}
