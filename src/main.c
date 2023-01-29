/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/01/29 13:11:53 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

char	advance(t_scanner *scanner)
{
	scanner->curr++;
	return (scanner->cmd[scanner->curr - 1]);
}

int	match(t_scanner *scanner, char expected)
{
	if (scanner->cmd[scanner->curr] != expected)
		return (FALSE);
	advance(scanner);
	return (TRUE);
}

void	init_scanner(t_scanner *scanner, const char *command)
{
	scanner->curr = 0;
	scanner->start = 0;
	scanner->cmd = command;
}

t_token		*make_token(t_scanner *scanner, t_tk_type type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->lexema = ft_substr(scanner->cmd, scanner->start,
			scanner->curr - scanner->start);
	token->tk_type = type;
	return (token);
}

t_token	*word_quote(t_scanner *scanner, char c)
{
	char	close;

	close = c;
	c = advance(scanner);
	while (c != 0 && c != close)
		c = advance(scanner);
	if (c == 0 && c != close)
		return (make_token(scanner, TK_ERROR));
	return (make_token(scanner, TK_WORD));
}

t_token	*word(t_scanner *scanner)
{
	char c;

	c = scanner->cmd[scanner->curr--];
	while (!ft_strchr(METACHARS, c))
		c = scanner->cmd[++scanner->curr];
	return (make_token(scanner, TK_WORD));
}

t_token	*scan_token(t_scanner *scanner)
{
	char	c;

	c = advance(scanner);
	if (c == '|')
		return(make_token(scanner, TK_PIPE));
	if (c == '<')
	{
		if (match(scanner, '<'))
			return (make_token(scanner, TK_DLESS));
		return (make_token(scanner, TK_LESS));		
	}
	if (c == '>')
	{
		if (match(scanner, '>'))
			return (make_token(scanner, TK_DGREAT));
		return (make_token(scanner, TK_GREAT));
	}
	else
	{
		if (ft_isquote(c))
			return (word_quote(scanner, c));
		return (word(scanner));
	}
}

int	main(void)
{
	t_scanner scanner;
	const char *command = "'ola'<<>>";

	init_scanner(&scanner, command);

	while (command[scanner.curr] != '\0') 
	{
		scanner.start = scanner.curr;
		t_token *tk = scan_token(&scanner);
		printf("%d | %s\n", tk->tk_type, tk->lexema);
		scanner.start = scanner.curr;
	}

	// char c = advance(&scanner);
	// char *test = NULL;
	// char close = c;
	// if (is_quote(c))
	// {
	// 	c = advance(&scanner);
	// 	while (c != 0 && c != close)
	// 		c = advance(&scanner);
	// 	if (c != 0 && c == close)
	// 		test = ft_substr(scanner.cmd, scanner.start, scanner.curr - scanner.start);
	// 	if (c == 0 && c != close)
	// 		printf("error");
	// }
	//char *test = ft_substr(scanner.cmd, scanner.start, scanner.curr - scanner.start);
	// printf("%s\n", test);
	// printf("%d\n", scanner.curr);
}
