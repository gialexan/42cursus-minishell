/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/04 00:10:18 by gialexan         ###   ########.fr       */
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

void	print_cmd(t_cmd *cmd)
{
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

void	lstclear(t_token *lst, void (*del)(void *))
{
	t_token	*tmp;
	t_token *next;

	if (!lst)
		return ;
	tmp = lst;
	next = tmp->next;
	del((void *)tmp->lexema);
	del(tmp);
	lstclear(next, del);
}

void	clear_dlst(t_cmd *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	lstclear(lst->list, del);
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

/* TO DO
 *
 * Verificar questão de redirecionadores, como eles funcionam e o preciso produzir sobre.
 *
 * Criar estrutura que executa os comandos.
 * Como vou me livrar dos nó da linkedlist que forem redirect
 * 1° Redirect a ser executado é sempre heredoc (dless)
 * 2° Redirect a ser executado é sempre input (less)
 * 3° Redirect a ser executado é sempre exit (great) e (dgreat). Obs: O que vale é qual está por último
 *
 *
 * run_cmdlst vai estar dentro da execute_command:
 * ls <<EOF -l > outfile < infile
 * cat > ./outfiles/outfiles1 < missing
 * cat > outfile < missing
 *
*/

void	exec_cmd(t_token *token, t_bool boolean) //essa função pode ter um ponteiro para uma função
{
	if (!token)
		return ;
	else if (match(type(token), TK_WORD)) //Aki vai executar depois que todos tk já forem executar.
	{
		exec_cmd(token->next, boolean);
		printf("%8s | %3s \n", "WORD", token->lexema);
		return ;
	}
	else if (match(type(token), TK_DLESS))
	{
		printf("%8s | %3s \n", "HEREDOC", token->lexema);
		return(exec_cmd(token->next, boolean));
	}
	else if (match(type(token), TK_LESS))
	{
		//aqui vai chamar a função de abrir arq.
		printf("%8s | %3s \n", "INPUT", token->lexema);
		//return(exec_cmd(token->next, função que retorna boolean));
		return(exec_cmd(token->next, TRUE));
	}
	else if (match(type(token), TK_GREAT) && boolean)
	{
		printf("%8s | %3s \n", "OUTPUT", token->lexema);
		return (exec_cmd(token->next, boolean));
	}
	else if (match(type(token), TK_DGREAT) && boolean)
	{
		printf("%8s | %3s \n", "APPEND", token->lexema);
		return (exec_cmd(token->next, boolean));
	}
	return (exec_cmd(token->next, FALSE));
}

void	run_cmdlst(t_cmd *cmd)
{
	if (!cmd)
		return ;
	exec_cmd(cmd->list, FALSE); //sempre enviar tudo como se fosse ter <
	return (run_cmdlst(cmd->next));
	/* Pode ou não limpar aqui. */
	/* clear_dlst(cmd, free);*/
}

int main(void)
{
    t_scanner	scanner;
    t_token		*token = NULL;
	t_cmd		*parser = NULL;

    char command[] = "<< EOF test1 ls < test cat <<EOF -l << EOF1 >> test > test | ls > out"; 
    scanner = init_scanner(command);

    token = lexical_analysis(&scanner, token);
	print_stack(token);

	parser = syntax_analysis(token);
	print_cmd(parser);
	//execute_command();

	//run_cmdlst(parser);
	//clear_dlst(parser, free);
	
	cat > ./outfiles/outfiles1 < missing
	-> cat > out < in
}
