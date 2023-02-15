/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/15 13:57:48 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"
#include <time.h>

//------------------------------------------SCANNER---------------------------------------------------------------//

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
	scanner->list = NULL;
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
	token->next = NULL;
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

	c = scanner->cmd[--scanner->curr];
	while (!ft_strchr(METACHARS, c))
		c = scanner->cmd[++scanner->curr];
	return (make_token(scanner, TK_WORD));
}

void	skip_space (t_scanner *scanner)
{
	while (ft_isspace(scanner->cmd[scanner->curr]))
		advance (scanner);
	scanner->start = scanner->curr;
}

int	is_at_end(t_scanner *scanner)
{
	return (scanner->cmd[scanner->curr] == 0);
}

t_token	*scan_token(t_scanner *scanner)
{
	char	c;

	skip_space(scanner);
	if (is_at_end(scanner))
		return (make_token(scanner, TK_EOF));
	c = advance(scanner);
	if (c == '|')
		return (make_token(scanner, TK_PIPE));
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

//------------------------------------------LINKED LIST---------------------------------------------------------------//

t_token	*lstlast(t_token *lst)
{
	if (lst)
		while (lst->next != NULL)
			lst = lst->next;
	return (lst);
}

void	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = lstlast(*lst);
		tmp->next = new;
	}
}

void	stack_token(t_scanner *scanner)
{
	if (scanner->curr >= ft_strlen(scanner->cmd))
		return ;
	scanner->start = scanner->curr;
	lstadd_back(&scanner->list, scan_token(scanner));
	stack_token(scanner);
}

void	print_stack(t_scanner *scanner)
{
	t_token *tmp;

	tmp = scanner->list;
	while(tmp != NULL)
	{
		printf("TK_TYPE -> %d   |   TK_LEXEMA -> %s\n", tmp->tk_type, tmp->lexema);
		tmp = tmp->next;
	}
}

//---------------------------------------TESTES---------------------------------------------------------------//

/*
 * To do:
 * Começar análise sintática
*/
int	main(void)
{
	t_scanner scanner;
	const char *command = "<<<>>>	|>|<<    |>>'ola42'\"ola42\"    ola42     ";
	init_scanner(&scanner, command);
	stack_token(&scanner);
	print_stack(&scanner);
}
