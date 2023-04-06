/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/05 23:39:31 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define GREEN_PROMPT "\e[m\e[1;32m❯ \e[m"

/* TO DO
 * Criar o executor de comando;
 * Pegar o exception dos file abertos;
 * Criar exit
*/

void	refresh_data(t_data *data)
{
	data->fd[STDIN_FILENO] = STDIN_FILENO;
	data->fd[STDOUT_FILENO] = STDOUT_FILENO;
	data->retcode = 0;
	data->error = FALSE;
}

void	execute_cmdlst(t_cmd *root, t_data *data)   
{
	t_list	*cmd;

	if (!root)
		return ;
	cmd = exec_redirect(root->token, data, NULL);
	exec_builtins(cmd, data);
	ft_lstclear(&cmd, free);
	refresh_data(data);
	execute_cmdlst(root->next, data);
	free(root);
}

void	execute(t_cmd *root)
{
	t_data	data;

	data.fd[STDIN_FILENO] = STDIN_FILENO;
	data.fd[STDOUT_FILENO] = STDOUT_FILENO;
	data.retcode = 0;
	data.error = FALSE;
	data.pipeline = FALSE;
	save_cmdlst_ref(root);
	execute_cmdlst(root, &data);
}

void	msh_loop(void)
{
	t_cmd		*root;
	t_list		*token;
    t_scanner	scanner;
	char 		*command;

	while (TRUE)
	{
		command = readline(GREEN_PROMPT);
		if (!ft_strncmp(command, "exit", 5))
			break ;
    	scanner = init_scanner(command);
    	token = lexical_analysis(&scanner, NULL);
		root = syntax_analysis(token);
		execute(root);
		free(command);
		command = NULL;
	}
	free(command);
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;

	init_envment(envp, get_envp());
	//init_arraypath();
	msh_loop();
	//clear_arraypath();
	clear_envment();
}


















/*
EXPORT TEST BASIC:
 char command[] = "export $test carro=moto";
    scanner = init_scanner(command);
    token = lexical_analysis(&scanner, token);
	parser = syntax_analysis(token);
	execute_cmdlst(parser, get_data());

	t_list *tmp = *get_envp();
	
	while(tmp != NULL)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	clear_arraypath();
	ft_lstclear(get_envp(), free);
*/

/*
UNSET TEST BASIC
char command[] = "unset $carro carro";
    scanner = init_scanner(command);
    token = lexical_analysis(&scanner, token);
	parser = syntax_analysis(token);
	execute_cmdlst(parser, get_data());

	delete_envp("carro", get_envp(), NULL);

	tmp = *get_envp();
	while(tmp != NULL)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}

	clear_arraypath();
	ft_lstclear(get_envp(), free);

*/