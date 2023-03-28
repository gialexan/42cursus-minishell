/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/27 22:05:15 by gialexan         ###   ########.fr       */
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
 * Criar expansor geral $pwd, $user
*/

/* 
void	init_exec(t_data *data)
{
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
	ft_lstclear(&tmp, free);
	execute_command(cmd->next, data);
	free(cmd);
}
*/

/**
 * Se for só as " é só expandir e fim de papo.
 * Se for só as ' precisa fazer parser de 2 em 2.
 * Se for misturado " e ' é só chorar.
 * Saber se todas estão abertas e fechadas? Contar " e ' depois separadas depois resto da divisão por 2
*/

static char	advance(t_scanner *scanner)
{
	scanner->current++;
	return (scanner->cmd[scanner->current - 1]);
}

char *slice_word(t_scanner *scanner)
{
	char c;

	c = advance(scanner);
	while (c != 0 && c != '\'' && c != '"')
		c = advance(scanner);
	scanner->current--;
	return (ft_substr(scanner->cmd, scanner->start,
		scanner->current - scanner->start));
}

char *slice_quotes(t_scanner *scanner)
{
	char c;
	char end;
	char *sliced;
	
	end = advance(scanner);
	c = advance(scanner);
	while (c != end && c != 0)
		c = advance(scanner);
	return (ft_substr(scanner->cmd, scanner->start,
		scanner->current - scanner->start));
}

t_list	*quotes_splitting(t_scanner *scanner, t_list *quotes)
{
	char *sliced;

	if (scanner->current >= ft_strlen(scanner->cmd))
		return (quotes);
	scanner->start = scanner->current;
	if (scanner->cmd[scanner->current] == '\'' || scanner->cmd[scanner->current] == '"')
		sliced = slice_quotes(scanner);
	else
		sliced = slice_word(scanner);
	
	ft_lstadd_back(&quotes, ft_lstnew(sliced));
	return (quotes_splitting(scanner, quotes));
}

char *variable_expansion(char *str)
{





	
	return (NULL);
}

void	word_splitting(void)
{
	t_scanner	scanner;
	t_list		*quotes = NULL;

	//"'ls''''''ola'oi''''bom dia   ''"
	char command[] = "\"''ls''\"";

	scanner = init_scanner(command);
	quotes = quotes_splitting(&scanner, quotes);
	print_stack(quotes, 0);

	// char *tmp = slice(&scanner);
	// printf("%s\n", tmp);
	// scanner.start = scanner.current;
	// tmp = slice(&scanner);
	// printf("%s\n", tmp);
	// scanner.start = scanner.current;
	// tmp = slice(&scanner);
	// printf("%s\n", tmp);
	
}

// echo "''" '''''" $PWD "''''' "''"
int main(int argc, char **argv, char **envp)  // echo "''" ''" $PWD "'' "''"
{
	t_data		data;
    t_list		*token = NULL;
	t_cmd		*parser = NULL;
    t_scanner	scanner;

	(void)argv;
	(void)envp;

	//char *test = \"''\"gilmar\"''\";

	// char *tmp = ft_strjoin(test, c);
	// printf("%s\n", tmp);

	//init_envment(envp, get_envp());

	//ft_lstclear(get_envp(), free);

	//"<'infile''''ls'''''>outfile | echo \"'''\"''\"'\"gilmar\"'\"''\"'''\""
    //char command[] = "echo 'ls'oi''";

    //scanner = init_scanner(command);
    //token = lexical_analysis(&scanner, token);
	//print_stack(token, 0);
	word_splitting();
	
	//parser = syntax_analysis(token);
	// data.readpipe = FALSE; //Arrumar lugar melhor para isso.
	// execute_command(parser, &data);
}
