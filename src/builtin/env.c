/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:57:20 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/09 14:57:20 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	write_output(t_list *token);

int	ft_env(t_list *token)
{
	t_list	*envp;

	if (token->next)
		return (EXIT_FAILURE);
	envp = *get_envp();
	if (envp)
		write_output(envp);
	else
	{
		msh_error("envp", "Environment doesn't exist.", 0);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	write_output(t_list *envp)
{
	if (!envp)
		return ;
	ft_putendl_fd(envp->content, STDOUT_FILENO);
	return (write_output(envp->next));
}
