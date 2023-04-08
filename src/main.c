/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/07 21:15:34 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define GREEN_PROMPT "\e[m\e[1;32m❯ \e[m"

void	msh_loop(void)
{
	t_cmd		*root;
	t_list		*token;
    t_scanner	scanner;
	char 		*command;

	while (TRUE)
	{
		set_interactive_hooks();
		
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
	init_arraypath();
	msh_loop();
	clear_arraypath();
	clear_envment();
}
