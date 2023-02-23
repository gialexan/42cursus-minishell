/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/23 17:08:09 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"
#include <time.h>

// //------------------------------------------SCANNER---------------------------------------------------------------//

// char	advance(t_scanner *scanner)
// {
// 	scanner->curr++;
// 	return (scanner->cmd[scanner->curr - 1]);
// }

// t_bool	match(t_scanner *scanner, char expected)
// {
// 	if (scanner->cmd[scanner->curr] != expected)
// 		return (FALSE);
// 	advance(scanner);
// 	return (TRUE);
// }

// void	init_scanner(t_scanner *scanner, const char *command)
// {
// 	scanner->curr = 0;
// 	scanner->cmd = command;
// }

// t_token	*make_token(t_scanner *scanner, t_tk_type type)
// {
// 	t_token *token;

// 	token = malloc(sizeof(t_token));
// 	if (!token)
// 		return (NULL);
// 	token->lexema = ft_substr(scanner->cmd, scanner->start,
// 			scanner->curr - scanner->start);
// 	token->tk_type = type;
// 	token->next = NULL;
// 	return (token);
// }

// t_token *string(t_scanner *scanner, char c)
// {
// 	char close;

// 	if (ft_isquote(c))
// 	{
// 		close = c;
// 		c = advance(scanner);
// 		while (c != 0 && c != close)
// 		c = advance(scanner);
// 		if (c == 0 && c != close)
// 			return (make_token(scanner, TK_ERROR));
// 		return (make_token(scanner, TK_WORD));
// 	}
// 	else
// 	{
// 		c = scanner->cmd[--scanner->curr];
// 		while (!ft_strchr(METACHARS, c))
// 		c = scanner->cmd[++scanner->curr];
// 		return (make_token(scanner, TK_WORD));
// 	}
// }

// void	skip_space (t_scanner *scanner)
// {
// 	while (ft_isspace(scanner->cmd[scanner->curr]))
// 		advance (scanner);
// 	scanner->start = scanner->curr;
// }

// t_token	*scan_token(t_scanner *scanner)
// {
// 	char	c;

// 	skip_space(scanner);
// 	c = advance(scanner);
// 	if (c == '\0')
// 		return (make_token(scanner, TK_EOF));
// 	else if (c == '|')
// 		return (make_token(scanner, TK_PIPE));
// 	else if (c == '<')
// 	{
// 		if (match(scanner, '<'))
// 			return (make_token(scanner, TK_DLESS));
// 		return (make_token(scanner, TK_LESS));	
// 	}
// 	else if (c == '>')
// 	{
// 		if (match(scanner, '>'))
// 			return (make_token(scanner, TK_DGREAT));
// 		return (make_token(scanner, TK_GREAT));
// 	}
// 	else
// 		return (string(scanner, c));
// }

// //------------------------------------------LINKED LIST---------------------------------------------------------------//

// t_token	*lstlast(t_token *lst)
// {
// 	if (lst)
// 		while (lst->next != NULL)
// 			lst = lst->next;
// 	return (lst);
// }

// void	lstadd_back(t_token **lst, t_token *new)
// {
// 	t_token	*tmp;

// 	if (!*lst)
// 		*lst = new;
// 	else
// 	{
// 		tmp = lstlast(*lst);
// 		tmp->next = new;
// 	}
// }

// t_token	*lexical_analysis(t_scanner *scanner, t_token *token)
// {
// 	if (scanner->curr > ft_strlen(scanner->cmd)) //if (scanner->curr >= ft_strlen(scanner->cmd) + 1)
// 		return (token);
// 	scanner->start = scanner->curr;
// 	lstadd_back(&token, scan_token(scanner));
// 	return (lexical_analysis(scanner, token));
// }

// void	print_stack(t_token *token)
// {
// 	t_token *tmp;

// 	tmp = token;
// 	while(tmp != NULL)
// 	{
// 		printf("TK_TYPE -> %d   |   TK_LEXEMA -> %s\n", tmp->tk_type, tmp->lexema);
// 		tmp = tmp->next;
// 	}
// }

// //---------------------------------------PARSER---------------------------------------------------------------//

// t_bool	parse(t_token *token);

// t_token *next(t_token *token)
// {
// 	return (token->next);
// }

// t_tk_type next_tk_type(t_token *token)
// {
// 	return (token->next->tk_type);
// }

// t_bool	word(t_token *token)
// {
// 	if (IS_WORD(token->tk_type))
// 	{
// 		printf("married: %s\n", token->lexema);
// 		if (next_tk_type(token) == TK_EOF)
// 			return (TRUE); //return (printf("success 2\n"));
// 		return (parse(next(token)));
// 	}
// 	return (FALSE); //printf("error2\n")
// }

// t_bool	parse(t_token *token)
// {
// 	printf("syntax: %s\n", token->lexema);
// 	if (IS_REDIRECTION(token->tk_type))
// 	{
// 		if (next_tk_type(token) == TK_EOF)
// 			return (FALSE); //return (printf("erro 1\n"))
// 		return (word(next(token)));
// 	}
// 	else if (IS_WORD(token->tk_type))
// 	{
// 		if (next_tk_type(token) == TK_EOF)
// 			return (TRUE); //return (printf("success 1\n"));
// 		return (parse(next(token)));
// 	}
// 	else if (IS_PIPE(token->tk_type))
// 	{
// 		if (next_tk_type(token) == TK_EOF)
// 			return (FALSE); //return (printf("erro 3\n"))
// 		else if (next_tk_type(token) == TK_PIPE)
// 			return (FALSE); //return (printf("erro 4\n"));
// 		return (parse(next(token)));
// 	}
// 	else
// 		return (FALSE);
// }

// t_bool syntax_analysis(t_token *token)
// {
// 	if (token == NULL)
// 		return (FALSE);
// 	else if (token->tk_type == TK_EOF)
// 		return (FALSE);
// 	else if (token->tk_type == TK_PIPE)
// 		return (FALSE);
// 	else
// 		return(parse(token));
// }

//---------------------------------------TESTES---------------------------------------------------------------//

/*
 * To do:
 * Finalizar análise sintática | parser
 *
 * Se chegou no token EOF e não encontrou nenhum token de erro pelo caminho
 * e nenhum problema gramática significa que está tudo certo?
 *
 * Se o token EOF for depois do redirecionador deve-se invalidar o comando?
 * Se o token EOF for primeiro token o que fazer?
 *
 *				<---------------------Lexical Analysis Testes---------------------->
 * teste:
 * 1 = "<<<>>>	|>|<<    |>>'ola42'\"ola42\"    ola42     "
 * 2 = "< infile ls -l -a -b -cd > outfile | < outfile"
 *
 *              <---------------------Syntax Analysis Testes----------------------->
 * No error:
 *	1 = < infile, 2 = ls > outfile, 3 = ls > outfile | cat infile, 4 = << infile >> outfile, 5 = ls wc-l
 * Error:
 *	1 = ls ||| wc -l, 2 = ls |, 3 = ls >, 4 = <, 5 = |, 6 = <<infile>>>, 7 = <<<infile, 8 = ls | >, 9 = ls > |
 *	"< ls -l -a -b -cd > 'test'"
*/

int main(void)
{
    // t_scanner	scanner;
    // t_bool		parser;
    // t_token		*token = NULL;

    // char command[] = "< algo";
    // init_scanner(&scanner, command);
    // token = lexical_analysis(&scanner, token);
    // print_stack(token);
    // parser = syntax_analysis(token);
	// printf("%d\n", parser);
	printf("TESTE\n");
}
