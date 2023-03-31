/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:00:02 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/31 10:38:46 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

t_list	*lexical_analysis(t_scanner *scanner, t_list *token)
{
	if (scanner->current > ft_strlen(scanner->cmd))
		return (token);
	scanner->start = scanner->current;
	ft_lstadd_back(&token, scan_token(scanner));
	return (lexical_analysis(scanner, token));
}

char	advance(t_scanner *scanner)
{
	scanner->current++;
	return (scanner->cmd[scanner->current - 1]);
}

t_scanner	init_scanner(const char *command)
{
	t_scanner scanner;

	scanner.current = 0;
	scanner.cmd = command;
	return (scanner);
}

void	skip_space(t_scanner *scanner)
{
	while (ft_isspace(scanner->cmd[scanner->current]))
		scanner->current++;
	scanner->start = scanner->current;
}

t_list *make_token(t_scanner *scanner, t_tk_type type)
{
	t_list *token;

	token = malloc(sizeof(t_list));
	if (!token)
		return (NULL);
	token->content = ft_substr(scanner->cmd, scanner->start,
			scanner->current - scanner->start);
	token->tk_type = type;
	token->next = NULL;
	return (token);
}
