/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:49:18 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/09 23:53:08 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"
#include "execute.h"

#define MAX_SAVED_POINTERS 100

void	msh_clear(void)
{
	clear_envment();
	clear_arraypath();
	rl_clear_history();
	clear_cmdlst(*get_cmdlst_ref(), free);
}

void	clear_cmdlst(t_cmd *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	ft_lstclear(&lst->token, del);
	clear_cmdlst(lst->next, del);
	del(lst);
	lst = NULL;
}

void    clear_arraypath(void)
{
    char ***path;
	char **tmp;

	path = get_path();
	if (!path)
		return ;
	tmp = *path;
    ft_free_split(tmp);
    *path = NULL;
}

void	clear_envment(void)
{
	ft_lstclear(get_envp(), free);
}

void	clear_heredoc(void)
{
	t_hdoc *clean;
	
	clean = get_clean();
	
	msh_clear();
	close(clean->fd);
	ft_lstclear(&clean->head, free);
	ft_lstclear(&clean->delimiter, free);
}
