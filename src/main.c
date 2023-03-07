/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:21:55 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/07 18:08:50 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print(t_token *token)
{
	printf("%8s | %3s | %3s\n", "HEREDOC", token->lexema, token->next->lexema);
}

void	print_stack(t_token *token, int type)
{
	t_token *tmp;
	tmp = token;
	if (type == 1)
	{
		printf("Command:\n\t");
		while(tmp != NULL)
		{
			printf("%s ", tmp->lexema);
			tmp = tmp->next;
		}
		printf("\n");
	}
	else
	{
		while(tmp != NULL)
		{
			printf("TK_TYPE -> %d   |   TK_LEXEMA -> %s\n", tmp->tk_type, tmp->lexema);
			tmp = tmp->next;
		}
	}
}

void	print_cmd(t_cmd *cmd)
{
    t_token *curr_token;
	int count;

	count = 0;
    while (cmd != NULL) {
        printf("Command %d :\n\t", ++count);
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

void	clear_dlst(t_cmd *lst, t_token *token, void (*del)(void *))
{
	if (!lst)
		return ;
	if (token != NULL)
		lstclear(token, del);
	else
		lstclear(lst->list, del);
	clear_dlst(lst->next, token, del);
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

/*
 * [<<] [EOF] [test1] [ls] [<] [test] [cat] [<<] [EOF] [-l] [<<] [EOF1] [>>] [test] [>] [test]
*/

static t_token *advanced(t_token **token)
{
	t_token *current;

	current = *token;
	*token = (*token)->next;
	current->next = NULL;
	return (current);
}

t_token *exec_redirect(t_token *token, t_token *head);

t_token *exec_input(t_token *token, t_token *c, t_token *head)
{
	t_token *filename = advanced(&token);
	lstdelone(c, free);
	lstdelone(filename, free);
	return (exec_redirect(token, head));
}

t_token *exec_heredoc(t_token *token, t_token *c, t_token *head)
{
	t_token *filename = advanced(&token);
	lstdelone(c, free);
	lstdelone(filename, free);
	return (exec_redirect(token, head));
}

t_token *exec_output(t_token *token, t_token *c, t_token *head)
{
	t_token *filename = advanced(&token);
	lstdelone(c, free);
	lstdelone(filename, free);
	return (exec_redirect(token, head));
}

t_token *exec_append(t_token *token, t_token *c, t_token *head)
{
	t_token *filename = advanced(&token);
	lstdelone(c, free);
	lstdelone(filename, free);
	return (exec_redirect(token, head));
}

t_token *exec_redirect(t_token *token, t_token *head)
{
	t_token *c;

    if (!token)
        return head;
	c = advanced(&token);
    if (match(type(c), TK_DLESS))
		return (exec_heredoc(token, c, head));
    else if (match(type(c), TK_LESS))
		return (exec_input(token, c, head));
    else if (match(type(c), TK_GREAT))
		return (exec_output(token, c, head));
    else if (match(type(c), TK_DGREAT))
		return (exec_append(token, c, head));
	lstadd_back(&head, c);
	return (exec_redirect(token, head));
}

void	run_cmdlst(t_cmd *cmd)
{
	if (!cmd)
		return ;
	t_token *tmp = exec_redirect(cmd->list, NULL);
	print_stack(tmp, 1);
	lstclear(tmp, free);
	run_cmdlst(cmd->next);
	free(cmd);
}

//"<< EOF test1  ls < test  cat <<EOF -l << EOF1 >> test > test"
int main(void)
{
    t_scanner	scanner;
    t_token		*token = NULL;
	t_cmd		*parser = NULL;

    char command[] = "<< EOF test1 | ls < test  | cat <<EOF -l << EOF1 >> test > test"; 
    scanner = init_scanner(command);

    token = lexical_analysis(&scanner, token);
	//print_stack(token, 0);

	parser = syntax_analysis(token);
	print_cmd(parser);

	//printf("\n\n");

	//execute_command();

	run_cmdlst(parser);
	
	// cat > ./outfiles/outfiles1 < missing
	// -> cat > out < in
	//clear_dlst(parser, free);
}
