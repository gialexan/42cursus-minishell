/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:38 by gialexan          #+#    #+#             */
/*   Updated: 2023/05/25 10:30:59 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_loop(void)
{
	t_cmd		*root;
	t_list		*token;
	t_scanner	scanner;
	char		*command;

	while (TRUE)
	{
		set_interactive_hooks();
		command = prompt();
		if (!command)
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

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	init_envment(envp, get_envp());
	init_arraypath();
	msh_loop();
	clear_envment();
	clear_arraypath();
}
