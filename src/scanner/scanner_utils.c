/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:00:02 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/07 19:46:59 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scanner.h>
#include <helper.h>

t_token	*lexical_analysis(t_scanner *scanner, t_token *token)
{
	if (scanner->curr > ft_strlen(scanner->cmd))
		return (token);
	scanner->start = scanner->curr;
	lstadd_back(&token, scan_token(scanner));
	return (lexical_analysis(scanner, token));
}

t_scanner	init_scanner(const char *command)
{
	t_scanner scanner;

	scanner.curr = 0;
	scanner.cmd = command;
	return (scanner);
}

void	skip_space (t_scanner *scanner)
{
	while (ft_isspace(scanner->cmd[scanner->curr]))
		scanner->curr++;
	scanner->start = scanner->curr;
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
