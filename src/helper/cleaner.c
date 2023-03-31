/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:49:18 by gialexan          #+#    #+#             */
/*   Updated: 2023/03/31 14:26:38 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

void	clear_dlst(t_cmd *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	ft_lstclear(&lst->token, del);
	clear_dlst(lst->next, del);
	del(lst);
}
