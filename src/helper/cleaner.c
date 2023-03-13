/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:49:18 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/13 13:48:01 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <helper.h>

void	lstclear(t_token *lst, void (*del)(void *))
{
	t_token	*tmp;
	t_token *next;

	if (!lst)
		return ;
	tmp = lst;
	next = tmp->next;
	del((void *)tmp->lexema);
	del(tmp);
	lstclear(next, del);
}

void	clear_dlst(t_cmd *lst, t_token *token, void (*del)(void *))
{
	if (!lst)
		return ;
	lstclear(lst->list, del);
	clear_dlst(lst->next, token, del);
	del(lst);
}
