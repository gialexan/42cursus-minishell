/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:49:18 by gialexan          #+#    #+#             */
/*   Updated: 2023/04/08 02:53:50 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"
#include "execute.h"

void	msh_clear(void)
{
	t_cmd **lst;

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
    void *tmp;
	
	path = get_path();
	if (!*path)
		return ;
	tmp = *path;
    ft_free_split(tmp);
    *path = NULL;
}

void	save_and_clean(t_list *ref, t_list *ref1, int type)
{
	static t_list *tmp;
	static t_list *tmp1;

	if (type == SAVE)
	{
		tmp = ref;
		tmp1 = ref1;
	}
	else if (type == CLEAN)
	{
		if (!tmp && !tmp1)
			return  ;
		ft_lstclear(&tmp, free);
		ft_lstdelone(tmp1, free);
	}
}

void	clear_envment(void)
{
	ft_lstclear(get_envp(), free);
}
