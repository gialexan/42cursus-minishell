/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:09:36 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 23:02:02 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

t_list **get_envp(void)
{
	static t_list *envp;

	return (&envp);
}

void	init_envment(char **environment, t_list **envp)
{
	t_list *new_node;

	if (!*environment)
		return ;
	new_node = ft_lstnew(ft_strdup(*environment));
	ft_lstadd_back(envp, new_node);
	return (init_envment(++environment, envp));
}
