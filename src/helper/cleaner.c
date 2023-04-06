/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:49:18 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/05 23:38:37 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"
#include "execute.h"

void	msh_clear(void)
{
	clear_envment();
	clear_cmdlst(*get_cmdlst_ref(), free);
}

void	clear_cmdlst(t_cmd *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	ft_lstclear(&lst->token, del);
	clear_cmdlst(lst->next, del);
	del(lst);
}

void    clear_arraypath(void)
{
    char ***path;
    void *tmp;
	
	path = get_path();
	tmp = *path;
    ft_free_split(tmp);
    path = NULL;
}

void	clear_envment(void)
{
	ft_lstclear(get_envp(), free);
}