/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_crud.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:08:36 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/17 10:29:07 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

t_list *search_envp(char *search, t_list *envp)
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

t_bool	delete_envp(char *delete, t_list **envp, t_list *prev)
{
	t_list	*tmp;
	int		lenght;

	if (!*envp)
		return (FALSE);
	tmp = *envp;
	if (!ft_strncmp(delete, tmp->content, 1))
	{
		lenght = ft_strlen(delete);
		if (!ft_strncmp(delete, tmp->content, lenght))
		{
			if (!prev)
				*envp = (*envp)->next;
			else if (prev && *envp)
				prev->next = (*envp)->next;
			free(tmp);
			tmp = NULL;
			return (TRUE);
		}
	}
	return (delete_envp(delete, &(*envp)->next, *envp));	
}

t_bool	insert_envp(char *insert, t_list **envp)
{
	if (!insert)
		return (FALSE);
	ft_lstadd_back(envp, ft_lstnew(insert));
	return (TRUE);
}

t_bool	update_envp(char *key, char *new, t_list *envp)
{
	t_list *update;

	update = search_envp(key, envp);
	if (!update)
		return FALSE;
	free(update->content);
	update->content = new;
	return (TRUE);
}