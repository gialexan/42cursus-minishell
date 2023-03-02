/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/02 15:01:10 by gialexan         ###   ########.fr       */
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

void print_cmd(t_cmd *cmd) {
    t_token *curr_token;
	int count;

	count = 0;
    while (cmd != NULL) {
        printf("Command %d:\n\t", ++count);
        curr_token = cmd->list;
        while (curr_token != NULL) {
            printf("%s ", curr_token->lexema);
            curr_token = curr_token->next;
        }
		printf("\n");
        cmd = cmd->next;
    }
}

void	lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;
	t_token *next;

	if (!*lst)
		return ;
	tmp = *lst;
	next = tmp->next;
	del((void *)tmp->lexema);
	del(tmp);
	lstclear(&next, del);
}

void	clear_dlst(t_cmd *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	lstclear(&lst->list, del);
	clear_dlst(lst->next, del);
	del(lst);
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
#include <unistd.h>

int main(void)
{
    t_scanner	scanner;
    t_token		*token = NULL;
	t_cmd		*parser = NULL;

    char command[] = "EOF"; 
    scanner = init_scanner(command);

    token = lexical_analysis(&scanner, token);
	print_stack(token);

	parser = syntax_analysis(token);
	print_cmd(parser);
	//exec_command()
	clear_dlst(parser, free);
	here_doc(command);
}
