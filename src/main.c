/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/19 09:53:44 by gialexan         ###   ########.fr       */
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

t_bool	match(t_scanner *scanner, char expected)
{
	if (scanner->cmd[scanner->curr] != expected)
		return (FALSE);
	advance(scanner);
	return (TRUE);
}

void	init_scanner(t_scanner *scanner, const char *command)
{
	scanner->curr = 0;
	scanner->cmd = command;
}

t_token	*make_token(t_scanner *scanner, t_tk_type type)
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

t_bool	is_at_end(t_scanner *scanner)
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

t_token	*lexical_analysis(t_scanner *scanner, t_token *token)
{
	if (scanner->curr >= ft_strlen(scanner->cmd))
		return (token);
	scanner->start = scanner->curr;
	lstadd_back(&token, scan_token(scanner));
	return (lexical_analysis(scanner, token));
}

void	print_stack(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while(tmp != NULL)
	{
		printf("TK_TYPE -> %d   |   TK_LEXEMA -> %s\n", tmp->tk_type, tmp->lexema);
		tmp = tmp->next;
	}
}

//---------------------------------------PARSER---------------------------------------------------------------//

/*
 * To do: Io_Word
 * Confirmar se o token que veio é type word, se for existe um proximo? se sim, chamar syntax error...
 * se não, o que devo retornar?
 *
*/

t_bool parse(t_token *token);

t_bool	marry(t_token *token, t_tk_type expected)
{
	if (token->tk_type == expected && token->next != NULL)
	{
		printf("consume: %s\n", token->lexema);
		return (parse(token->next));
	}
	else if (token->tk_type == expected)
	{
		printf("consume: %s\n", token->lexema);
		return (printf("success 2\n")); //"<ls -l -a -b -cd>test" esse teste sai aqui.
	}
	return (printf("error2\n"));
}

t_bool	parse(t_token *token)
{
	printf("syntax: %s\n", token->lexema);
	// if (token == NULL)
	// 	return (printf("test\n"));
	if (token->tk_type == TK_LESS || token->tk_type == TK_GREAT
		|| token->tk_type == TK_DLESS || token->tk_type == TK_DGREAT)
	{
		if (token->next == NULL)
			return (printf("erro 1\n")); //Se não houver next depois redirecionadores retorna erro pq precisa arq.
		return (marry(token->next, TK_WORD)); //Se ouver next vai para IO_WORD validar token.
	}
	else if (token->tk_type == TK_WORD)
	{
		if (token->next == NULL)
			return (printf("success 1\n")); //Se for apenas 1 comando EX: ls.
		return (parse(token->next)); // Se não vai para recursiva validar gramática.
	}
	else if (token->tk_type == TK_PIPE)
	{
		if (token->next == NULL)
			return (printf("erro 3\n"));
		else if (token->next->tk_type == TK_PIPE)
			return (printf("erro 4\n"));
		return (parse(token->next));
	}
	else
		return (FALSE);
}

t_bool syntax_analisys(t_token *token)
{
	if (token == NULL)
		return (FALSE);
	else if (token->tk_type == TK_PIPE)
		return (FALSE);
	return(parse(token));
}

//---------------------------------------TESTES---------------------------------------------------------------//

/*
 * To do:
 * Começar análise sintática | parser
 *
 * Se chegou no token EOF e não encontrou nenhum token de erro pelo caminho
 * e nenhum problema gramática significa que está tudo certo?
 *
 * testes:
 * "<<<>>>	|>|<<    |>>'ola42'\"ola42\"    ola42     "
 * "< infile ls -l -a -b -cd > outfile | < outfile"
 *
 *              <---------------------True Parser Testes---------------------->
 *	1 = < infile, 2 = ls > outfile, 3 = ls > outfile | cat, 4 = << infile >> outfile, ls wc-l,
 *	1 = ls ||| wc -l, 2 = ls |, 3 = ls >, 4 = <, 5 = |, 10 = <<infile>>>, 11 = <<<infile, 12 = ls | >, 13 = ls > |,
 *
 *
 *
 *
*/
 
int main(void)
{
    t_scanner scanner;
    t_token *token = NULL;
    t_bool parser;

    const char command[] = "ls ||| wc-l";

    init_scanner(&scanner, command);
    token = lexical_analysis(&scanner, token);
    print_stack(token);
    parser = syntax_analisys(token);
}
