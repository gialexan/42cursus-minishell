/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/09 10:36:04 by gialexan         ###   ########.fr       */
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

void	init_exec(t_execute *exc)
{
	exc->fd[STDIN_FILENO] = STDIN_FILENO;
	exc->fd[STDOUT_FILENO] = STDOUT_FILENO;
	exc->error = FALSE;
}

void	execute(t_cmd *cmd)
{
	t_token		*tmp;
	t_execute	exc;

	if (!cmd)
		return ;
	init_exec(&exc);
	tmp = exec_redirect(cmd->list, &exc, NULL);
	//print_stack(tmp, 1);
	lstclear(tmp, free);
	execute(cmd->next);
	free(cmd);
}

/*
 *"<< EOF test1  ls < test  cat <<EOF -l << EOF1 >> test > test"
 *
 * echo "Olá, 42 São Paulo!" > /tmp/heredoc.txt
*/
int main(void)
{
    t_scanner	scanner;
    t_token		*token = NULL;
	t_cmd		*parser = NULL;

    char command[] = "<< EOF ls ";
    scanner = init_scanner(command);

    token = lexical_analysis(&scanner, token);
	//print_stack(token, 0);

	parser = syntax_analysis(token);
	//print_cmd(parser);
	//printf("\n");
	execute(parser);

	//printf("stdin = %d    | stdout = %d     | stderr = %d\n", STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
}
