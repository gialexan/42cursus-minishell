/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:49:18 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 18:47:54 by gialexan         ###   ########.fr       */
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

void	save_and_clean(t_list *saveptr, t_action action)
{
	static t_list	*savedptr[MAX_SAVED_POINTERS];
	static int		num_ptr_saved;

	if (action == SAVE_ACTION)
		savedptr[num_ptr_saved++] = saveptr;
	else if (action == CLEAN_ACTION)
	{
		while (num_ptr_saved--)
			ft_lstclear(&savedptr[num_ptr_saved], free);
	}
}

void	clear_envment(void)
{
	ft_lstclear(get_envp(), free);
}
