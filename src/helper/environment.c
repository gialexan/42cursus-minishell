/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:09:36 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 21:09:58 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

t_list **get_env(void)
{
	static t_list *envp;

	return (&envp);
}

void	init_envment(char **envpment, t_list **envp)
{
	t_list *new_node;

	if (!*envpment)
		return ;
	new_node = ft_lstnew(ft_strdup(*envpment));
	ft_lstadd_back(envp, new_node);
	return (init_envment(++envpment, envp));
}