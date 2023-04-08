/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:51:31 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 18:43:00 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

# define TOO_MANY_ARGS "too many arguments"

int	ft_exit(t_list *str)
{
	(void)str;
	msh_clear();
	exit(*get_exit_code());
}

/*
static void	die_full(char *location, char *message, int exit_status)
{
	int	errno_status;

	errno_status = errno;
	msh_error(location, message, STDERR_FILENO);
	clean_up();
	if (exit_status == -1)
		exit(errno_status);
	exit(exit_status);
}

static int	get_exit_status(t_list *tokens)
{
	if (tokens == NULL)
		return (0);
	return (ft_atoi(tokens->content));
}

int	my_exit(t_list *token)
{
	int		exit_status;

	if (ft_lstsize(token) > 2)
	{
		msh_error(exit, "too many arguments", 0);
		exit(-1);
	}
	clean_up();
	
	printf(MY_EXIT "\n");
	exit_status = get_exit_status(token->next);
	ft_lstclear(&token, free);
	exit(exit_status);
	return (EXIT_SUCCESS);
}
*/