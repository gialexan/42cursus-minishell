/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/05 09:39:07 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO DO
 * Criar o executor de comando;
 * Pegar o exception dos file abertos;
 * Criar exit
*/

#define GREEN_PROMPT "\e[m\e[1;32m❯ \e[m"

void	init_data(t_data *data)
{
	data->fd[STDIN_FILENO] = STDIN_FILENO;
	data->fd[STDOUT_FILENO] = STDOUT_FILENO;
	data->retcode = 0;
	data->error = FALSE;
}

void	execute_cmdlst(t_cmd *cmd, t_data *data)   
{
	t_list	*tmp;

	if (!cmd)
		return ;
	init_data(data);
	tmp = exec_redirect(cmd->token, data, NULL);
	exec_builtins(tmp, data);
	ft_lstclear(&tmp, free);
	execute_cmdlst(cmd->next, data);
	free(cmd);
}

void	msh_loop(void)
{
    t_scanner	scanner;
	t_list		*token;
	t_cmd		*parser;
	
	char *command = "";
	while (TRUE)
	{
		token = NULL;
		parser = NULL;
		command = readline(GREEN_PROMPT);
		if (!ft_strncmp(command, "exit", 5))
		{
			free(command);
			break ;
		}
    	scanner = init_scanner(command);
    	token = lexical_analysis(&scanner, token);
		parser = syntax_analysis(token);
		execute_cmdlst(parser, get_data());
		free(command);
		command = NULL;
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;

	init_envment(envp, get_envp());
	init_arraypath();
	msh_loop();
	clear_arraypath();
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