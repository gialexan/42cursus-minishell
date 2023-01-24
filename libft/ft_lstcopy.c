/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:41:26 by gialexan          #+#    #+#             */
/*   Updated: 2022/12/20 19:53:12 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*ft_lstcopy(t_list *lst)
{
	t_stack	*node;

	if (lst == NULL)
		return (NULL);
	else
	{
		node = malloc(sizeof(t_stack));
		node->number = lst->number;
		node->index = lst->index;
		node->next = lstcopy(lst->next);
	}
	return (node);
}
