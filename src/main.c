/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/08 11:01:22 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* TO DO
 *
 * Verificar questão de redirecionadores, como vou salvar o fd? Exceptions heredoc?.
 *
 * run_cmdlst vai estar dentro da execute_command:
 * ls <<EOF -l > outfile < infile
 * cat > ./outfiles/outfiles1 < missing
 * cat > outfile < missing
 *
*/

/*
 * [<<] [EOF] [test1] [ls] [<] [test] [cat] [<<] [EOF] [-l] [<<] [EOF1] [>>] [test] [>] [test]
*/

void	execute_command(t_cmd *cmd)
{
	t_token *tmp;

	if (!cmd)
		return ;
	tmp = exec_redirect(cmd->list, NULL);
	//print_stack(tmp, 1);
	lstclear(tmp, free);
	execute_command(cmd->next);
	free(cmd);
}

/*
 *"<< EOF test1  ls < test  cat <<EOF -l << EOF1 >> test > test"
*/

int main(void)
{
    t_scanner	scanner;
    t_token		*token = NULL;
	t_cmd		*parser = NULL;

    char command[] = "<< EOF";
    scanner = init_scanner(command);

    token = lexical_analysis(&scanner, token);
	//print_stack(token, 0);

	parser = syntax_analysis(token);
	print_cmd(parser);
	//printf("\n");
	execute_command(parser);
}
