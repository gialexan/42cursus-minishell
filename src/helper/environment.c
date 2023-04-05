/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:08:36 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/05 13:58:40 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

void	init_envment(char **environment, t_list **envp)
{
	t_list *new_node;

	if (!*environment)
		return ;
	new_node = ft_lstnew(ft_strdup(*environment));
	ft_lstadd_back(envp, new_node);
	return (init_envment(++environment, envp));
}

t_list *search_envp(const char *search, t_list *envp)
{
	int lenght;

	if (!envp)
		return (NULL);
	else if (!ft_strncmp(search, envp->content, 1))
	{
		lenght = ft_strlen(search);
		if (!ft_strncmp(search, envp->content, lenght))
			return (envp);
	}
	return (search_envp(search, envp->next));
}

t_bool	delete_envp(const char *dell, t_list **envp, t_list *prev)
{
	t_list	*tmp;
	int		lenght;

	if (!*envp)
		return (FALSE);
	tmp = *envp;
	if (!ft_strncmp(dell, tmp->content, 1))
	{
		lenght = ft_strlen(dell);
		if (!ft_strncmp(dell, tmp->content, lenght))
		{
			if (!prev)
				*envp = (*envp)->next;
			else if (prev && *envp)
				prev->next = (*envp)->next;
			free(tmp->content);
			free(tmp);
			return (TRUE);
		}
	}
	return (delete_envp(dell, &(*envp)->next, *envp));
}

t_bool	insert_envp(const char *insert, t_list **envp)
{
	if (!insert)
		return (FALSE);
	ft_lstadd_back(envp, ft_lstnew(ft_strdup(insert)));
	return (TRUE);
}

t_bool	update_envp(const char *update, t_list *envp)
{
	if (!update)
		return (FALSE);
	free(envp->content);
	envp->content = ft_strdup(update);
	return (TRUE);
}
