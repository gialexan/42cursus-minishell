/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/03 20:27:41 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO DO
 * Criar o executor de comando;
 * Pegar o exception dos file abertos;
 * Criar expansor de arquivos;
 * Criar exit
*/

void	init_data(t_data *data)
{
	data->fd[STDIN_FILENO] = STDIN_FILENO;
	data->fd[STDOUT_FILENO] = STDOUT_FILENO;
	data->retcode = 0;
	data->error = FALSE;
}

void	exec_builtins(t_list *token, t_data *data)
{
	char *tmp;

	if (!token)
		return ;
	token->content = expandchr(token->content);
	if (!ft_strncmp(token->content, "export", 6))
		ft_export(token);
	else if (!ft_strncmp(token->content, "unset", 5))
		ft_unset(token);
	else if (!ft_strncmp(token->content, "echo", 5))
		ft_echo(token);
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
	t_list		*token = NULL;
	t_cmd		*parser = NULL;

	char command[] = "unset test test1";
    scanner = init_scanner(command);
    token = lexical_analysis(&scanner, token);
	parser = syntax_analysis(token);
	execute_cmdlst(parser, get_data());
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	init_envment(envp, get_envp());
	init_arraypath();
	msh_loop();
	clear_arraypath();
	ft_lstclear(get_envp(), free);
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