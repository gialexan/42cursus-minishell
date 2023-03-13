/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 13:35:22 by gialexan         ###   ########.fr       */
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
 * [<<] [EOF] [test1] [ls] [<] [test] [cat] [<<] [EOF] [-l] [<<] [EOF1] [>>] [test] [>] [test]
*/

/* TO DO
 *
 * Exceptions heredoc?.
 *
 * run_cmdlst vai estar dentro da execute_command:
 * ls <<EOF -l > outfile < infile
 * cat > ./outfiles/outfiles1 < missing
 * cat > outfile < missing
 *
*/

void	init_exec(t_data *data)
{
	data->fd[STDIN_FILENO] = STDIN_FILENO;
	data->fd[STDOUT_FILENO] = STDOUT_FILENO;
	data->retcode = 0;
	data->error = FALSE;
}

void	execute_command(t_cmd *cmd, t_data *data)
{
	t_token	*tmp;

	if (!cmd)
		return ;
	init_exec(data);
	tmp = exec_redirect(cmd->list, data, NULL);
	lstclear(tmp, free);
	execute_command(cmd->next, data);
	free(cmd);
}

/*
 *"<< EOF test1  ls < test  cat <<EOF -l << EOF1 >> test > test"
 *
 * echo "Olá, 42 São Paulo!" > /tmp/heredoc.txt
*/

int main(void)
{
	t_data		data;
    t_scanner	scanner;
    t_token		*token = NULL;
	t_cmd		*parser = NULL;
	
    // char command[] = "< infile ls > outfile | ls > outfile -a";

    // scanner = init_scanner(command);
    // token = lexical_analysis(&scanner, token);
	// parser = syntax_analysis(token);
	// execute_command(parser, &data);
}


/*
void	execute(t_cmd *cmd, t_data *data)
{
	t_token	*tmp;
	if (!cmd)
		return ;
	init_exec(data);
	printf("Command %d\n", data->count++);
	printf("\tbefore: %d\n", data->fd[STDIN_FILENO]);
	printf("\tbefore: %d\n", data->fd[STDOUT_FILENO]);
	tmp = exec_redirect(cmd->list, data, NULL);
	printf("\tafter: %d\n", data->fd[STDIN_FILENO]);
	printf("\tafter: %d\n", data->fd[STDOUT_FILENO]);
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	close(data->fd[STDIN_FILENO]);
	close(data->fd[STDOUT_FILENO]);
	//print_stack(tmp, 1);
	lstclear(tmp, free);
	execute(cmd->next, data);
	free(cmd);
}

int main(void)
{
	t_data		data;
    t_scanner	scanner;
    t_token		*token = NULL;
	t_cmd		*parser = NULL;

    char command[] = "< infile ls > outfile | ls > outfile -a";

    scanner = init_scanner(command);
    token = lexical_analysis(&scanner, token);
	//print_stack(token, 0);
	parser = syntax_analysis(token);
	//print_cmd(parser);
	//printf("\n");
	data.count = 1;
	execute(parser, &data);
}
*/
