/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 00:00:02 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 14:11:11 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scanner.h>
#include <helper.h>

t_list	*lexical_analysis(t_scanner *scanner, t_list *token)
{
	if (scanner->curr > ft_strlen(scanner->cmd))
		return (token);
	scanner->start = scanner->curr;
	ft_lstadd_back(&token, scan_token(scanner));
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

t_list *make_token(t_scanner *scanner, t_tk_type type)
{
	t_list *token;

	token = malloc(sizeof(t_list));
	if (!token)
		return (NULL);
	token->content = ft_substr(scanner->cmd, scanner->start,
			scanner->curr - scanner->start);
	token->tk_type = type;
	token->next = NULL;
	return (token);
}
