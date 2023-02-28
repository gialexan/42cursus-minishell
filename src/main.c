/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/02/28 22:30:50 by gialexan         ###   ########.fr       */
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
void	lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		del((void *)tmp->lexema);
		free(tmp);
	}
	*lst = NULL;
}
void print_cmd(t_cmd *cmd);

int main(void)
{
    t_scanner	scanner;
    t_token		*token = NULL;
	t_cmd		*parser = NULL;

    char command[] = "test1 | test2 | test3 | test4 | test5 | test6 | test7"; //< ls
    scanner = init_scanner(command);
    token = lexical_analysis(&scanner, token);

	print_stack(token);
	parser = syntax_analysis(token);
	print_cmd(parser);
	
	token = NULL;
	t_cmd *test = parser;
	while(test != NULL)
	{
		t_cmd *aux = test;
		lstclear(&aux->list, free);
		test = test->next;
		free(aux);
	}
}

void print_cmd(t_cmd *cmd) {
    t_token *curr_token;

    while (cmd != NULL) {
        printf("Command:\n");
        curr_token = cmd->list;
        while (curr_token != NULL) {
            printf("\t%s\n", curr_token->lexema);
            curr_token = curr_token->next;
        }
        cmd = cmd->next;
    }
}