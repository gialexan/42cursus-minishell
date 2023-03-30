/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/30 07:57:40 by gialexan         ###   ########.fr       */
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
 * 4 = "<'infile''''ls'''''>outfile | echo \"'''\"''\"'\"gilmar\"'\"''\"'''\""
 *
 *              <---------------------Syntax Analysis Testes----------------------->
 * No error:
 *	1 = < infile, 2 = ls > outfile, 3 = ls > outfile | cat infile, 4 = << infile >> outfile, 5 = ls wc-l
 * Error:
 *	1 = ls ||| wc -l, 2 = ls |, 3 = ls >, 4 = <, 5 = |, 6 = <<infile>>>, 7 = <<<infile, 8 = ls | >, 9 = ls > |
 *
 * [<<] [EOF] [test1] [ls] [<] [test] [cat] [<<] [EOF] [-l] [<<] [EOF1] [>>] [test] [>] [test]
 *
 *              <---------------------Coisas Aleatórios----------------------->
 * run_cmdlst vai estar dentro da execute_command:
 * ls <<EOF -l > outfile < infile
 * cat > ./outfiles/outfiles1 < missing
 * cat > outfile < missing
 * "<< EOF test1  ls < test  cat <<EOF -l << EOF1 >> test > test"
 * echo "Olá, 42 São Paulo!" > /tmp/heredoc.txt
*/

/* TO DO
 * Criar o executor de comando;
 * Pegar o exception dos file abertos;
 * Criar expansor de arquivos;
 * Criar exit
*/

/*
void	init_exec(t_data *data)
{
	if (data->read - true)
		return ;
	data->fd[STDIN_FILENO] = STDIN_FILENO;
	data->fd[STDOUT_FILENO] = STDOUT_FILENO;
	data->retcode = 0;
	data->error = FALSE;
}

void	execute_command(t_cmd *cmd, t_data *data)   
{
	t_list	*tmp;

	if (!cmd)
		return ;
	init_exec(data);
	tmp = exec_redirect(cmd->token, data, NULL);
	exec_bultins(cmd->token, data);
	ft_lstclear(&tmp, free);
	execute_command(cmd->next, data);
	free(cmd);
}
*/

//\"'''$USER'''\"
// echo "''" '''''" $PWD "''''' "''"
// echo "''" ''" $PWD "'' "''"
//"'ls''''''ola'oi''''bom dia   ''" -> "'ls'''''\"'ola'\"oi''''bomdia"
int main(int argc, char **argv, char **envp)
{
	t_data		data;
    t_list		*token = NULL;
	t_cmd		*parser = NULL;
    t_scanner	scanner;

	(void)argv;
	(void)envp;

	init_envment(envp, get_envp());

	expand();

	ft_lstclear(get_envp(), free);

    return 0;

	//"<'infile''''ls'''''>outfile | echo \"'''\"''\"'\"gilmar\"'\"''\"'''\""
    //char command[] = "echo 'ls'oi''";

    //scanner = init_scanner(command);
    //token = lexical_analysis(&scanner, token);
	//print_stack(token, 0);
	//word_splitting();
	// parser = syntax_analysis(token);
	// data.readpipe = FALSE; //Arrumar lugar melhor para isso.
	// execute_command(parser, &data);
}
