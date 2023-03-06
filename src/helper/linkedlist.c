/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:18:19 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/06 21:55:07 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <helper.h>

t_token	*lstlast(t_token *lst)
{
	if (lst)
		while (lst->next != NULL)
			lst = lst->next;
	return (lst);
}

void	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = lstlast(*lst);
		tmp->next = new;
	}
}

void	lstdelone(t_token *lst, void (*del)(void*))
{
	del((void *)lst->lexema);
	del(lst);
	lst = NULL;
}
