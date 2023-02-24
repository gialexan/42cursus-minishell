/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/24 15:09:35 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * 3 = "< ls -l -a -b -cd > 'test'"
 *
 *              <---------------------Syntax Analysis Testes----------------------->
 * No error:
 *	1 = < infile, 2 = ls > outfile, 3 = ls > outfile | cat infile, 4 = << infile >> outfile, 5 = ls wc-l
 * Error:
 *	1 = ls ||| wc -l, 2 = ls |, 3 = ls >, 4 = <, 5 = |, 6 = <<infile>>>, 7 = <<<infile, 8 = ls | >, 9 = ls > |
 *
*/

int main(void)
{
    t_scanner	scanner;
    t_bool		parser;
    t_token		*token = NULL;

    char command[] = "ls wc-l";
    init_scanner(&scanner, command);
    token = lexical_analysis(&scanner, token);
    print_stack(token);
    parser = syntax_analysis(token);
	if (parser == 0)
		printf("Comando inválido!\n");
	else
		printf("Comando válido!\n");

}
